cmake_minimum_required(VERSION 3.13)

# Include the Raspberry Pi Pico SDK import script
include("pico_sdk_import.cmake")

# Project
project(Pico_I2C_LCD C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Set default build type to Release
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
    message("Using by default the Release build")
endif ()

# Set Debug build compiler arguments
set(CMAKE_CXX_FLAGS_DEBUG "-pipe -g -O0 -Wfatal-errors -Wpedantic -Wall -Wextra -Wshadow=local -Wdouble-promotion -Wformat=2 -Wformat-overflow=2 -Wformat-nonliteral -Wformat-security -Wformat-truncation=2 -Wnull-dereference -Wimplicit-fallthrough=3 -Wshift-overflow=2 -Wswitch-default -Wunused-parameter -Wunused-const-variable=2 -Wstrict-overflow=4 -Wstringop-overflow=3 -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wmissing-noreturn -Wsuggest-attribute=malloc -Wsuggest-attribute=format -Wmissing-format-attribute -Wsuggest-attribute=cold -Walloc-zero -Walloca -Wattribute-alias=2 -Wduplicated-branches -Wcast-qual")
set(CMAKE_C_FLAGS_DEBUG "-pipe -g -O0 -Wfatal-errors -Wpedantic -Wall -Wextra -Wshadow=local -Wdouble-promotion -Wformat=2 -Wformat-overflow=2 -Wformat-nonliteral -Wformat-security -Wformat-truncation=2 -Wnull-dereference -Wimplicit-fallthrough=3 -Wshift-overflow=2 -Wswitch-default -Wunused-parameter -Wunused-const-variable=2 -Wstrict-overflow=4 -Wstringop-overflow=3 -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wmissing-noreturn -Wsuggest-attribute=malloc -Wsuggest-attribute=format -Wmissing-format-attribute -Wsuggest-attribute=cold -Walloc-zero -Walloca -Wattribute-alias=2 -Wduplicated-branches -Wcast-qual")

# Set Release build compiler arguments
set(CMAKE_CXX_FLAGS_RELEASE "-pipe -O2 -fno-builtin")
set(CMAKE_C_FLAGS_RELEASE "-pipe -O2 -fno-builtin")

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Set the two examples directories
add_subdirectory(16x2-Display)
add_subdirectory(20x4-Display)
