@echo off

SETLOCAL EnableDelayedExpansion

set enable_unit_test=0
set enable_submodule_update=0
set windows_sdk_version=0

echo =======================
echo ==== SIMD Workshop ====
echo =======================

echo ==== Generating Project Files ====
if exist "./build_vs2017_win64/" (
  del ".\build_vs2017_win64\CMakeCache.txt"
)

mkdir build_vs2017_win64
cd build_vs2017_win64

echo cmake -DCMAKE_SYSTEM_VERSION=%windows_sdk_version% -G "Visual Studio 16 2019" -A x64 ..
cmake -DCMAKE_SYSTEM_VERSION=%windows_sdk_version% -G "Visual Studio 16 2019" -A x64 ..

if errorlevel 1 (
    echo ==== CMake finished with errors ====
    pause
    EXIT 1
)

echo ==== Install Finished ====
pause
EXIT
