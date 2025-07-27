#pragma once

#include <string>

#include "Utils/VulkanRAII.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace VulkanEngine
{
    class VulkanWindow
    {
    public:
        VulkanWindow(int width, int height, const std::string windowName);
        ~VulkanWindow();

        VulkanWindow(const VulkanWindow &) = delete;
        VulkanWindow &operator=(const VulkanWindow &) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); };
        vk::Extent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; };
        GLFWwindow* getGLFWWindow() const { return window; }

    private:
        void initWindow();

        int width;
        int height;

        std::string windowName;
        GLFWwindow *window;
    };
}