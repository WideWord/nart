#pragma once

struct GLFWwindow;

namespace nart {
    
    class UserInput {
    private:
        GLFWwindow* window;
    public:
        UserInput(GLFWwindow* window) { this->window = window; }
        
        bool getKey(int code);
    };
    
}
