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
1. git clone https://github.com/microsoft/vcpkg.git
2. cd vcpkg
3. bootstrap-vcpkg.bat
4. Create env. variable `VCPKG_ROOT`, set to vcpkg directory
5. Modify PATH env. variable, add vcpkg directory
6. open terminal, cd to project `DDS_image_converter` directory
7. create build directory `mkdir build`
8. Go to build directory `cd build`
9. Configure project `cmake --preset "vcpkg" ..` for Visual Studio 2022
10. Open Visual Studio, open project sln file in build directory, compile release or debug
