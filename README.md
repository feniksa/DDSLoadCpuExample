# DDS frame buffer data to image converter

DDS to PNG/RAW image converter

<img alt="lena dashboard image" src="https://github.com/feniksa/DDSLoadCpuExample/blob/main/docs/lena.png?raw=true" width="100" />

# Usage

To convert `input.dds` into `out.png` execute command

`$ ddsload.exe input.dds output.png` 


To convert `input.dds` into raw image `out.raw` execute command

`$ ddsload.exe input.dds output.raw`

# How to compile on windows 10
1. git clone https://github.com/microsoft/vcpkg.git
2. cd vcpkg
3. bootstrap-vcpkg.bat
4. Create env. variable `VCPKG_ROOT`, set to vcpkg directory
5. Modify PATH env. variable, add vcpkg directory
6. open terminal, cd to `DDSLoadCpuExample` directory
7. create build directory
8. cd build
9. `cmake --preset "vcpkg" ..`
10. Open Visual Studio, compile
