@echo off

SETLOCAL EnableDelayedExpansion

set enable_unit_test=0
set enable_submodule_update=0
set windows_sdk_version=0

echo =======================
echo ==== SIMD Workshop ====
echo =======================

echo ==== Generating Project Files ====
if exist "./vsproject/" (
  del ".\vsproject\CMakeCache.txt"
)

FOR /F "delims=" %%i IN ('dir "C:\Program Files (x86)\Windows Kits\10\Include" /b /ad-h /t:c /o-n') DO (
    SET windows_sdk_version=%%i
    GOTO :found
)
call :colorEcho %red% No Windows SDK found in location: C:\Program Files (x86)\Windows Kits\10\Include
EXIT 1
:found
SET windows_sdk_version=%CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION%
echo Latest installed Windows SDK: %windows_sdk_version%
echo Windows SDK required: 10.0.17763.0 or newer

mkdir vsproject
cd vsproject

echo cmake -G "Visual Studio 16 2019" -A x64 ..
cmake -G "Visual Studio 16 2019" -A x64 ..

if errorlevel 1 (
    echo ==== CMake finished with errors ====
    pause
    EXIT 1
)

echo ==== Install Finished ====
pause
EXIT
