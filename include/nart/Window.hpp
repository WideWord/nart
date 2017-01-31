#pragma once

struct GLFWwindow;

namespace nart {
    
    class Renderer;
    
    class Window {
    private:
        GLFWwindow* window;
        Renderer* renderer;
    public:
        struct Config {
            int width;
            int height;
            Config() {
                width = 800;
                height = 600;
            }
        };
        Window(Config cfg = Config());
        ~Window();
        void update();
        bool isShouldClose();
        Renderer& getRenderer();
    };
    
}
