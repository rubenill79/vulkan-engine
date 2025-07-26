#pragma once

#include "VulkanWindow.hpp"

namespace VulkanEngine
{
    class VulkanContext
    {
    public:
        static constexpr int width = 800;
        static constexpr int height = 600;

        VulkanContext();
        ~VulkanContext();

        VulkanContext(const VulkanContext &) = delete;
        VulkanContext &operator=(const VulkanContext &) = delete;

        void run();

    private:
        VulkanWindow window{width, height, "Hello World!"};
    };
}