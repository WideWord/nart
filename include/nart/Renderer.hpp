#pragma once

#include <nart/Typedef.hpp>

namespace nart {
    
    class RenderPass;
    
    class Renderer {
    public:
        std::string getDescription();
        //void addRenderPass(Ref<RenderPass> renderPass);
        void renderFrame();
    };
    
    
}
