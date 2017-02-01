#pragma once

struct GLFWwindow;

#include <nart/Typedef.hpp>

namespace nart {
    
    class Renderer;
    class UserInput;
    
    class System : public std::enable_shared_from_this<System> {
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
        System(const Config& cfg);
        
        static Ref<System> create(const Config& cfg = Config()) { return std::make_shared<System>(cfg); }
        
        ~System();
        void update();
        bool isShouldClose();
        Ref<Renderer> getRenderer();
        Ref<UserInput> getUserInput() { return userInput; }
        
        void getWindowSize(int& width, int& height);
        float getTimeDelta() { return deltaTime; }
        void setClipboard(const std::string& str);
        std::string getClipboard();
        const char* getClipboardCStr();
    };
    
}
