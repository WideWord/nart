#pragma once

struct GLFWwindow;

#include <nart/Typedef.hpp>

namespace nart {
    
    class Renderer;
    class UserInput;
    
    class Window {
    private:
        GLFWwindow* window;
        Ref<Renderer> renderer;
        Ref<UserInput> userInput;
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
        Ref<Renderer> getRenderer() { return renderer; }
        Ref<UserInput> getUserInput() { return userInput; }
    };
    
}
