#include "VulkanRenderer.hpp"

namespace VulkanEngine
{
    VulkanRenderer::VulkanRenderer(VulkanWindow &window, VulkanDevice &device) : window(window), device(device)
    {
        recreateSwapChain();
    }

    VulkanRenderer::~VulkanRenderer() {}

    void VulkanRenderer::recreateSwapChain()
    {
        auto extent = window.getExtent();
        while (extent.width == 0 || extent.height == 0)
        {
            extent = window.getExtent();
            glfwWaitEvents();
        }
        // Recreate the swap chain when the window is resized or needs to be recreated
        swapChain = std::make_unique<VulkanSwapChain>(device, extent);
    }
}