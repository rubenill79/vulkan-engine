#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

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
        GLFWwindow* getGLFWWindow() const { return window; }

    private:
        void initWindow();

        int width;
        int height;

        std::string windowName;
        GLFWwindow *window;
    };
}