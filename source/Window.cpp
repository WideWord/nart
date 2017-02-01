#include <nart/Window.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <nart/Renderer.hpp>
#include <nart/UserInput.hpp>

namespace nart {
    
    Window::Window(const Config& cfg) {
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
    
    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
    void Window::update() {
        glfwPollEvents();
        glfwSwapBuffers(window);
        auto newTime = glfwGetTime();
        deltaTime = (float)(newTime - lastFrameTime);
        lastFrameTime = newTime;
    }
    
    bool Window::isShouldClose() {
        return glfwWindowShouldClose(window);
    }
    
    Ref<Renderer> Window::getRenderer() {
        if (renderer == nullptr) {
            renderer = std::make_shared<Renderer>(shared_from_this());
        }
        return renderer;
    }
    
    void Window::getWindowSize(int& width, int& height) {
        glfwGetWindowSize(window, &width, &height);
    }
    
}
