cmake_minimum_required(VERSION 3.26)

project(VoxelEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "Source/*.cpp")
file(GLOB_RECURSE HEADERS "Source/*.h")

add_library(VoxelEngine STATIC ${SOURCES} ${HEADERS})

# Buscar dependencias
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Módulo Vulkan-Hpp (vulkan.hpp)
add_library(VulkanCppModule)
add_library(Vulkan::cppm ALIAS VulkanCppModule)

target_compile_definitions(VulkanCppModule
    PUBLIC VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1 VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1
)
target_include_directories(VulkanCppModule
    PUBLIC "${Vulkan_INCLUDE_DIR}"
)
target_link_libraries(VulkanCppModule
    PUBLIC Vulkan::Vulkan
)
set_target_properties(VulkanCppModule PROPERTIES CXX_STANDARD 20)

target_sources(VulkanCppModule
    PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS 
    "${Vulkan_INCLUDE_DIR}"
    FILES 
    "${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm"
)

# Incluir directorios y linkear librerías a VoxelEngine
target_include_directories(VoxelEngine PUBLIC
    "${Vulkan_INCLUDE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source"
    $<TARGET_PROPERTY:glfw,INTERFACE_INCLUDE_DIRECTORIES>
)
target_link_libraries(VoxelEngine PUBLIC Vulkan::cppm glfw glm::glm)

set(STB_INCLUDEDIR ${stb_INCLUDE_DIRS})
target_include_directories (VoxelEngine PUBLIC ${STB_INCLUDEDIR})

execute_process(
    COMMAND ./shaders.bat
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Copiar DLLs necesarias al directorio de salida de Game.exe
set(GLFW_DLL_PATH "${CMAKE_SOURCE_DIR}/External/Source/vcpkg_installed/x64-windows/bin/glfw3.dll")
set(VULKAN_DLL_PATH "$ENV{VULKAN_SDK}/Bin/vulkan-1.dll")
set(GAME_DEBUG_DIR "${CMAKE_BINARY_DIR}/Game/Debug")
set(GAME_RELEASE_DIR "${CMAKE_BINARY_DIR}/Game/Release")

if(EXISTS "${GLFW_DLL_PATH}")
    add_custom_command(TARGET VoxelEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLFW_DLL_PATH}"
            "${GAME_DEBUG_DIR}/glfw3.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLFW_DLL_PATH}"
            "${GAME_RELEASE_DIR}/glfw3.dll"
        COMMENT "Copiando glfw3.dll a Game/Debug y Game/Release"
    )
else()
    message(WARNING "No se encontró glfw3.dll en ${GLFW_DLL_PATH}, no se copiará la DLL.")
endif()