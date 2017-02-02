#include "System.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.hpp"
#include "UserInput.hpp"

namespace nart {
    
    System::System(const Config& cfg) {
        glfwInit();
        
#ifdef NART_PLATFORM_OSX
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
        
        window = glfwCreateWindow(cfg.width, cfg.height, "", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        auto err = glewInit();
        if (err != GLEW_OK) {
            std::cout << "Failed to init GLEW: " << glewGetErrorString(err) << '\n';
        }
        
        userInput = std::make_shared<UserInput>(window);
        lastFrameTime = glfwGetTime();
        deltaTime = 0;
        
    }
    
    System::~System() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
    void System::update() {
        userInput->newFrame();
        glfwPollEvents();
        glfwSwapBuffers(window);
        
        
        double newTime = glfwGetTime();
        deltaTime = (float)(newTime - lastFrameTime);

        if (framerateLimit > 0) {
            double deltaTarget = 1.0 / (double)framerateLimit;
            while (deltaTime < deltaTarget) {
                glfwPollEvents();
                double newTime = glfwGetTime();
                deltaTime = (float)(newTime - lastFrameTime);
            }
        }
        
        lastFrameTime = newTime;
    }
    
    bool System::isShouldClose() {
        return glfwWindowShouldClose(window);
    }
    
    Ref<Renderer> System::getRenderer() {
        if (renderer == nullptr) {
            renderer = std::make_shared<Renderer>(shared_from_this());
        }
        return renderer;
    }
    
    void System::getWindowSize(int& width, int& height) {
        glfwGetWindowSize(window, &width, &height);
    }
    
    void System::setClipboard(const std::string& str) {
        glfwSetClipboardString(window, str.c_str());
    }
    
    std::string System::getClipboard() {
        return std::string(glfwGetClipboardString(window));
    }
    
    const char* System::getClipboardCStr() {
        return glfwGetClipboardString(window);
    }
    
}
