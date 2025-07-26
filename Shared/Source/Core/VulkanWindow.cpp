#include "VulkanWindow.hpp"

namespace VulkanEngine
{
    VulkanWindow::VulkanWindow(int width, int height, const std::string windowName) : width{width}, height{height}, windowName{windowName}
    {
        initWindow();
    }

    VulkanWindow::~VulkanWindow()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void VulkanWindow::initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

        glfwSetWindowUserPointer(window, this);
        //glfwSetFramebufferSizeCallback(window, framebufferResizeCallback); TODO
    }
}