#pragma once

#include <nart/Typedef.hpp>
#include <nart/ShaderProgram.hpp>
#include <nart/VertexArray.hpp>
#include <nart/RenderPass.hpp>
#include <vector>

namespace nart {
    
    class RenderPass;
    
    class Renderer {
    private:
        std::vector<Ref<RenderPass>> renderPasses;
    public:
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
    };
    
    
}
