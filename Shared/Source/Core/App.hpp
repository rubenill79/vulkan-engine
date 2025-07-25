#pragma once
#include <GLFW/glfw3.h>

namespace VoxelEngine
{
    class App
    {
    public:
        App();
        void run();

    private:
        GLFWwindow *window = nullptr;
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();
    };
}