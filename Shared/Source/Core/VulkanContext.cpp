#include "VulkanContext.hpp"

namespace VulkanEngine
{
    VulkanContext::VulkanContext() {}

    VulkanContext::~VulkanContext() {}

    void VulkanContext::run()
    {
        while (!window.shouldClose()) {
            glfwPollEvents();
        }
    }
}