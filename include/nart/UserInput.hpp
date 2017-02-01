#pragma once

#include <vector>
#include "Typedef.hpp"

struct GLFWwindow;

namespace nart {
    
    class System;
    
    class UserInput {
    private:
        GLFWwindow* window;
        std::vector<uint32_t> inputBuffer;
        float deltaScroll;
        static UserInput* current;
        static void onMouseScroll(GLFWwindow* wnd, double dx, double dy);
        static void onCharInput(GLFWwindow* wnd, uint32_t character, int32_t mods);
        static void onKeyDown(GLFWwindow* wnd, int key, int scancode, int action, int mods);
    protected:
        friend class System;
        void newFrame();
    public:
        UserInput(GLFWwindow* window);
        
        bool getKey(int code);
        void getMousePosition(int& x, int& y);
        bool getMouseButton(int button);
        float getDeltaScroll() { return deltaScroll; }
        inline const std::vector<uint32_t>& getInputBuffer() const { return inputBuffer; }
    };
    
}
