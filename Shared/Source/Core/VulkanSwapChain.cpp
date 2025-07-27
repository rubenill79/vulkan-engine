#include "VulkanSwapChain.hpp"

namespace VulkanEngine
{

    static vk::Format chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) {
        const auto formatIt = std::ranges::find_if(availableFormats,
        [](const auto& format) {
            return format.format == vk::Format::eB8G8R8A8Srgb &&
                   format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
        });
        return formatIt != availableFormats.end() ? formatIt->format : availableFormats[0].format;
    }

    static vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) {
        return std::ranges::any_of(availablePresentModes,
            [](const vk::PresentModeKHR value) { return vk::PresentModeKHR::eMailbox == value; } ) ? vk::PresentModeKHR::eMailbox : vk::PresentModeKHR::eFifo;
    }
    
    VulkanSwapChain::VulkanSwapChain(VulkanDevice &device, vk::Extent2D windowExtent) : device(device), windowExtent(windowExtent)
    {
        init();
    }

    VulkanSwapChain::~VulkanSwapChain() {}

    void VulkanSwapChain::init()
    {
        createSwapChain();
    }

    void VulkanSwapChain::createSwapChain() {
        auto surfaceCapabilities = device.getPhysicalDevice().getSurfaceCapabilitiesKHR(device.getSurface());
        swapChainImageFormat = chooseSwapSurfaceFormat(device.getPhysicalDevice().getSurfaceFormatsKHR(device.getSurface()));
        swapChainExtent = chooseSwapExtent(surfaceCapabilities);
        auto minImageCount = std::max(3u, surfaceCapabilities.minImageCount);
        minImageCount = (surfaceCapabilities.maxImageCount > 0 && minImageCount > surfaceCapabilities.maxImageCount) ? surfaceCapabilities.maxImageCount : minImageCount;
        vk::SwapchainCreateInfoKHR swapChainCreateInfo{
            .surface = device.getSurface(), .minImageCount = minImageCount,
            .imageFormat = swapChainImageFormat, .imageColorSpace = vk::ColorSpaceKHR::eSrgbNonlinear,
            .imageExtent = swapChainExtent, .imageArrayLayers =1,
            .imageUsage = vk::ImageUsageFlagBits::eColorAttachment, .imageSharingMode = vk::SharingMode::eExclusive,
            .preTransform = surfaceCapabilities.currentTransform, .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
            .presentMode = chooseSwapPresentMode(device.getPhysicalDevice().getSurfacePresentModesKHR( device.getSurface() )),
            .clipped = true };

        swapChain = vk::raii::SwapchainKHR(device.getDevice(), swapChainCreateInfo);
        swapChainImages = swapChain.getImages();
    }

    vk::Extent2D VulkanSwapChain::chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        }
        return {
            std::clamp<uint32_t>(windowExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
            std::clamp<uint32_t>(windowExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height)
        };
    }
}