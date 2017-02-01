#pragma once

struct GLFWwindow;

#include <nart/Typedef.hpp>

namespace nart {
    
    class Renderer;
    class UserInput;
    
    class Window : public std::enable_shared_from_this<Window> {
    private:
        GLFWwindow* window;
        Ref<Renderer> renderer;
        Ref<UserInput> userInput;
        double lastFrameTime;
        float deltaTime;
    public:
        struct Config {
            int width;
            int height;
            Config() {
                width = 800;
                height = 600;
            }
        };
        Window(const Config& cfg);
        
        static Ref<Window> create(const Config& cfg = Config()) { return std::make_shared<Window>(cfg); }
        
        ~Window();
        void update();
        bool isShouldClose();
        Ref<Renderer> getRenderer();
        Ref<UserInput> getUserInput() { return userInput; }
        
        void getWindowSize(int& width, int& height);
        float getTimeDelta() { return deltaTime; }
    };
    
}
