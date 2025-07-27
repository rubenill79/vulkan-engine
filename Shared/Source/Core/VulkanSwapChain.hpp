#pragma once

#include "Utils/VulkanRAII.hpp"

#include "VulkanDevice.hpp"

namespace VulkanEngine
{
    class VulkanSwapChain
    {
    public:
        VulkanSwapChain(VulkanDevice &device, vk::Extent2D windowExtent);
        ~VulkanSwapChain();

        VulkanSwapChain(const VulkanSwapChain &) = delete;
        VulkanSwapChain &operator=(const VulkanSwapChain &) = delete;

    private:
        void init();
        void createSwapChain();

        // Helper functions
        vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities);

        vk::Format swapChainImageFormat = vk::Format::eUndefined;
        vk::Extent2D swapChainExtent;

        std::vector<vk::Image> swapChainImages;
        std::vector<vk::raii::ImageView> swapChainImageViews;

        VulkanDevice &device;
        vk::Extent2D windowExtent;

        vk::raii::SwapchainKHR swapChain = nullptr;
    };
}