#include <nart/Renderer.hpp>
#include <nart/RenderPass.hpp>
#include "OpenGL.hpp"

namespace nart {
  
    std::string Renderer::getDescription() {
        return "OpenGL Renderer";
    }
    
    void Renderer::renderPass(const Ref<nart::RenderPass>& pass) {
        renderPasses.push_back(pass);
    }
    
    
    void Renderer::renderFrame() {
        for (auto& pass : renderPasses) {
            
            glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
            glViewport(0, 0, 800, 600);
            glDisable(GL_CULL_FACE);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            for (auto& dc : pass->getDrawCalls()) {
                glUseProgram(dc.shaderProgram->getID());
                
                for (auto& constant : dc.constants.getItems()) {
                    switch (constant.type) {
                        case DrawConstantsBlock::Item::Type::Float:
                            glUniform1fv(constant.binding, 1, constant.rawData.floatData);
                        case DrawConstantsBlock::Item::Type::Vector2:
                            glUniform2fv(constant.binding, 1, constant.rawData.floatData);
                        case DrawConstantsBlock::Item::Type::Vector3:
                            glUniform3fv(constant.binding, 1, constant.rawData.floatData);
                        case DrawConstantsBlock::Item::Type::Vector4:
                            glUniform4fv(constant.binding, 1, constant.rawData.floatData);
                        case DrawConstantsBlock::Item::Type::Matrix2:
                            glUniformMatrix2fv(constant.binding, 1, GL_FALSE, constant.rawData.floatData);
                        case DrawConstantsBlock::Item::Type::Matrix3:
                            glUniformMatrix3fv(constant.binding, 1, GL_FALSE, constant.rawData.floatData);
                        case DrawConstantsBlock::Item::Type::Matrix4:
                            glUniformMatrix4fv(constant.binding, 1, GL_FALSE, constant.rawData.floatData);
                    }
                }
                
                glBindVertexArray(dc.vertexBuffer->getVAO());
                
                glDrawElements(GL_TRIANGLES, dc.vertexBuffer->getIndiciesCount(), GL_UNSIGNED_INT, nullptr);
            }
            
            pass->clear();
        }
        renderPasses.clear();
    }

}
