#pragma once

#include "Typedef.hpp"
#include "ShaderProgram.hpp"
#include "VertexArray.hpp"
#include "RenderPass.hpp"
#include "Texture2D.hpp"
#include <vector>

namespace nart {
    
    class RenderPass;
    class System;
    
    class Renderer {
    private:
        std::vector<Ref<RenderPass>> renderPasses;
        WRef<System> system;
    public:
        Renderer(const Ref<System>& system) {
            this->system = system;
        }
        
        std::string getDescription();
        void renderPass(const Ref<RenderPass>& pass);
        void renderFrame();
        
        inline Ref<Shader> createShader(const char* source, Shader::Type::Enum type) {
            return std::make_shared<Shader>(source, type);
        }
        
        inline Ref<ShaderProgram> createShaderProgram(const Ref<Shader>& vertexShader, const Ref<Shader>& fragmentShader) {
            return std::make_shared<ShaderProgram>(vertexShader, fragmentShader);
        }
        
        inline Ref<VertexArray> createVertexArray(const VertexArray::Description& description) {
            return std::make_shared<VertexArray>(description);
        }
        
        inline Ref<RenderPass> createRenderPass() {
            return std::make_shared<RenderPass>();
        }
        
        inline Ref<Texture2D> createTexture2D(const Texture2D::Description& desc) {
            return std::make_shared<Texture2D>(desc);
        }
    };
    
    
}
