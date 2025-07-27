#pragma once

#include "VulkanWindow.hpp"

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#ifdef __INTELLISENSE__
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif

namespace VulkanEngine
{
    class VulkanDevice
    {
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
    public:
        VulkanDevice(VulkanWindow &window);
        ~VulkanDevice();

        VulkanDevice(const VulkanDevice &) = delete;
        VulkanDevice &operator=(const VulkanDevice &) = delete;
        VulkanDevice(VulkanDevice &&) = delete;
        VulkanDevice &operator=(VulkanDevice &&) = delete;

    private:
        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();

        // Helper functions
        bool isDeviceSuitable(vk::raii::PhysicalDevice device);

        std::vector<const char *> getRequiredExtensions();

        vk::raii::Context context;
        vk::raii::Instance instance = nullptr;
        vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;

        vk::raii::PhysicalDevice physicalDevice = nullptr;
        vk::raii::Device device = nullptr;
        vk::raii::SurfaceKHR surface = nullptr;
        vk::raii::Queue graphicsQueue = nullptr;
        vk::raii::Queue presentQueue = nullptr;

        VulkanWindow &window;

        const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
        const std::vector<const char *> requiredDeviceExtension = {vk::KHRSwapchainExtensionName, vk::KHRSpirv14ExtensionName, vk::KHRSynchronization2ExtensionName, vk::KHRCreateRenderpass2ExtensionName};
    };
}