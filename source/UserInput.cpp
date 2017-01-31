#include <nart/UserInput.hpp>
#include "OpenGL.hpp"

namespace nart {
    
    bool UserInput::getKey(int code) {
        return glfwGetKey(window, code) == GLFW_PRESS;
    }
    
}
