# SIMD Workshop
### Introduction for using intrinsics in C++
#### Breda University of Applied Sciences, IGAD

Codebase used during the workshop

To compile this yourself:
- Download repository
- run install.bat
- open ./vsproject
- open solution and compile

#### requirements:
- windows 10
- visual Studio 19 (17 might work. change cmake call in install.bat)
- CMake 3.13 or higher
- Modern processor. (most project use SSE4, some might use up to AVX2)

#### content
- **example_1**, what is SIMD
- **example_2**, store and access your data while using intrinsics
- **example_3**, data location and order in memory
- **example_4**, a Mandelbrot fractal. "Practical SIMD Programming" - J. Bikker (2017)
- **example_5**, using QuickMath
- **QuickMath**, simplistic math library implementing basic math operations often seen in game development.
