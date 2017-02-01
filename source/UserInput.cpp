#include <nart/UserInput.hpp>
#include "OpenGL.hpp"

namespace nart {
    
    UserInput::UserInput(GLFWwindow* window) {
        this->window = window;
        current = this;
        glfwSetScrollCallback(window, UserInput::onMouseScroll);
        glfwSetCharModsCallback(window, UserInput::onCharInput);
        glfwSetKeyCallback(window, UserInput::onKeyDown);
    }
    
    bool UserInput::getKey(int code) {
        return glfwGetKey(window, code) == GLFW_PRESS;
    }
    
    void UserInput::getMousePosition(int& x, int& y) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        x = xpos;
        y = ypos;
    }
    
    void UserInput::newFrame() {
        inputBuffer.clear();
        deltaScroll = 0;
    }
    
    bool UserInput::getMouseButton(int button) {
        return glfwGetMouseButton(window, button);
    }
    
    UserInput* UserInput::current;
    
    void UserInput::onMouseScroll(GLFWwindow *wnd, double dx, double dy) {
        current->deltaScroll += (float)dy;
    }
    
    void UserInput::onCharInput(GLFWwindow *wnd, uint32_t character, int32_t mods) {
        current->inputBuffer.push_back(character);
    }
    
    void UserInput::onKeyDown(GLFWwindow* wnd, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            if (key == GLFW_KEY_BACKSPACE) {
                
            }
        }
            
    }
    
}
