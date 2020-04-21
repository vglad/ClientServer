<#
    .SYNOPSIS
    Powershell build script using CMake
    .DESCRIPTION
    Usage: ./build.sp1 [[-CMakePath <file_path>] [-Compiler [Clang|MSVC]] [-BuildType [Debug|Release]] [-SkipTests]]

        -CMakePath        Path to cmake.exe if it is not in your system/user $PATH variable
        -BuildType        Can be one of [Debug|Release], default=Release
        -Compiler         Can be one of [Clang|MSVC], default=Clang
        -SkipTests        Do not build tests
    .EXAMPLE
    .\build.ps1
    To build "Release" configuration and all tests
    .EXAMPLE
    .\build.ps1 -BuildType Debug -SkipTests
    To build "Debug" configuration and skip tests building
    .EXAMPLE
    .\build.ps1 -CMakePath C:\cmake-3.17.0\bin\cmake.exe -BuildType Debug
    To build "Debug" configuration and all tests using CMake 3.17.0
#>

Param(
  [String]$CMakePath,
  [ValidateSet("Debug", "Release")]
  [String]$BuildType = "Release",
  [ValidateSet("Clang", "MSVC")]
  [String]$Compiler = "Clang",
  [Switch]$SkipTests
)

# Setting CMake path
[String]$cmake = "cmake"
if ($CMakePath) {
  if (!(Test-Path $CMakePath -PathType Leaf -Include $cmake)) {
    Write-Output "No cmake.exe found in -CMakePath parameter."
    Exit 1
  } else {
    $cmake = $CMakePath
  }
}

# Setting build directory
[String]$BuildDir = $PSScriptRoot + "\build\" + $BuildType
if (!(Test-Path $BuildDir -PathType Container)) {
  New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null
}
Set-Location $BuildDir

# Setting tests build
[String]$tests_path = $BuildDir + '\test\' + $BuildType + '\tests.exe'
[String]$NoTests = "OFF"
if ($SkipTests -eq $true) {
  $NoTests = "ON"
}

# Set compiler and flags
# For clang compiler add clang.exe, clang++.exe and ninja.exe generator
# to PATH environment variable
[String]$generator_flag     = ''
[String]$generator_name     = ''
[String]$compiler_c         = ''
[String]$compiler_cxx       = ''
[String]$compiler_cxx_flags = ''

if ($Compiler -eq "Clang") {
  $generator_flag     = '-G'
  $generator_name     = 'Ninja'
  $compiler_c         = '-DCMAKE_C_COMPILER:STRING=clang'
  $compiler_cxx       = '-DCMAKE_CXX_COMPILER:STRING=clang++'
  $compiler_cxx_flags = '-DCMAKE_CXX_FLAGS="-m64 -Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wno-language-extension-token -Wno-gnu-anonymous-struct"'
  $tests_path         = $BuildDir + '\test\tests.exe'
} else {
  # Setting Visual Studio variables
  [String]$VSPath = $(& 'C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe' `
                      -latest -property installationPath)
  & $VSPath'\VC\Auxiliary\Build\vcvarsall.bat' 'x64'
  $compiler_cxx_flags = '-DCMAKE_CXX_FLAGS="/EHsc /W4 /WX"'
}

# Configure CMake and build
[String]$GeneratorFlag   = $generator_flag
[String]$GeneratorName   = $generator_name
[String]$C_Compiler      = $compiler_c
[String]$CXX_Compiler    = $compiler_cxx
[String]$CXX_Flags       = $compiler_cxx_flags
[String]$BuildTests      = '-DSKIP_TESTS=' + $NoTests
[String]$CMakeFilePath   = '../..'
[String]$Verbose         = '' #change to '--debug-output' if needed
[String[]]$arguments     = @($GeneratorFlag, $GeneratorName, `
                             $C_Compiler, $CXX_Compiler, $CXX_Flags, `
                             $BuildTests, $CMakeFilePath, $Verbose)
& $cmake @arguments

$arguments = @('--build', '.', '--config', $BuildType)
& $cmake @arguments

# Run tests
if ($SkipTests -ne $true) {
  & $tests_path
}
