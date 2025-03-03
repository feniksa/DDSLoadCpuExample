set(HEADERS
        imagetool.h
)
set(SOURCES
        imagetool.cpp
        main.cpp
)

add_executable(ddsloader ${HEADERS} ${SOURCES})
target_link_libraries(ddsloader PRIVATE Microsoft::DirectXTex)

if (MSVC)
    target_compile_options(ddsloader PRIVATE
            /W4             # Enable high warning level
            /WX             # Treat warnings as errors
            /MP             # Enable multi-threaded compilation
            /permissive-    # Enforce standard C++ compliance
    )

    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(ddsloader PRIVATE /O2 /GL) # Enable whole-program optimization
        target_link_options(ddsloader PRIVATE /LTCG)      # Enable link-time code generation
    elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
        # enable saniziers
        target_compile_options(ddsloader PRIVATE /Zi /Od /RTC1)
        target_link_options(ddsloader PRIVATE /DEBUG)
    endif()
endif()

install(TARGETS ddsloader RUNTIME DESTINATION bin)
