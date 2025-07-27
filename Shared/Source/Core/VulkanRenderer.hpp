#pragma once

#include "Utils/VulkanRAII.hpp"

#include "VulkanWindow.hpp"
#include "VulkanDevice.hpp"
#include "VulkanSwapChain.hpp"

namespace VulkanEngine
{
    class VulkanRenderer
    {
    public:
        VulkanRenderer(VulkanWindow &window, VulkanDevice &device);
        ~VulkanRenderer();

        VulkanRenderer(const VulkanRenderer &) = delete;
        VulkanRenderer &operator=(const VulkanRenderer &) = delete;

    private:
        void recreateSwapChain();

        VulkanWindow &window;
        VulkanDevice &device;
        std::unique_ptr<VulkanSwapChain> swapChain;
    };
}