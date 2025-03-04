# DDS frame buffer data to image converter

DDS to PNG/RAW image converter

<p align="center">
<img alt="lena dashboard image" src="https://github.com/feniksa/DDSLoadCpuExample/blob/main/docs/lena.png?raw=true" width="300" />
</p>

# Usage

To convert `input.dds` into `output.png` execute command

`$ ddsload.exe input.dds output.png` 


To convert `input.dds` into raw image `output.raw` execute command

`$ ddsload.exe input.dds output.raw`

# Supported platforms

* Windows 10
* Windows 11

# Dependencies

* DirectXTex

# How to compile on windows 10
1. Clone vckpg C++ package manager `git clone https://github.com/microsoft/vcpkg.git`
2. Go to cloned directory `cd vcpkg`
3. Execute `bootstrap-vcpkg.bat`
4. Create env. variable `VCPKG_ROOT`, set to vcpkg directory
5. Modify PATH env. variable, add vcpkg directory
6. Clone _DDS_image_converter_ project (this one) `git clone git@github.com:feniksa/DDS_image_converter.git`
7. Go to cloned project root `cd DDS_image_converter`
7. Create build directory `mkdir build`
8. Go to build directory `cd build`
9. Configure project `cmake --preset "vcpkg" ..` for Visual Studio 2022
10. Open Visual Studio, open project sln file in build directory, compile release or debug
