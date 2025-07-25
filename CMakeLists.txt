# CMake raíz (opcional, solo si quieres superproyecto)
cmake_minimum_required(VERSION 3.29)
project(VulkanGame LANGUAGES CXX)

# Habilita módulos C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

include_directories(Shared/Source)

add_subdirectory(Shared)

include(CMake/ExecutableProject.cmake)
add_subdirectory(Game)