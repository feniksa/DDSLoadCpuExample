cmake_minimum_required(VERSION 3.30)
project(dssloader)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(directxtex CONFIG REQUIRED)

set(HEADERS
        imagetool.h
)
set(SOURCES
        imagetool.cpp
        main.cpp
)

add_executable(dssloader ${HEADERS} ${SOURCES})
target_link_libraries(dssloader PRIVATE Microsoft::DirectXTex)

if (MSVC)
    target_compile_options(dssloader PRIVATE
            /W4             # Enable high warning level
            /WX             # Treat warnings as errors
            /MP             # Enable multi-threaded compilation
            /permissive-    # Enforce standard C++ compliance
    )

    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(dssloader PRIVATE /O2 /GL) # Enable whole-program optimization
        target_link_options(dssloader PRIVATE /LTCG)      # Enable link-time code generation
    elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
        # enable saniziers
        target_compile_options(dssloader PRIVATE /Zi /Od /RTC1)
        target_link_options(dssloader PRIVATE /DEBUG)
    endif()
endif()

install(TARGETS dssloader RUNTIME DESTINATION bin)
