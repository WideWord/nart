#include <nart/Window.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <nart/Renderer.hpp>

namespace nart {
    
    Window::Window(Config cfg) {
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
        
        renderer = new Renderer();
    }
    
    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
    void Window::update() {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    bool Window::isShouldClose() {
        return glfwWindowShouldClose(window);
    }
    
    Renderer& Window::getRenderer() {
        return *renderer;
    }
    
}
