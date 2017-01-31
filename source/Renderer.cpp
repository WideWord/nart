#include <nart/Renderer.hpp>
#include <nart/RenderPass.hpp>
#include <nart/Texture2D.hpp>
#include <nart/Window.hpp>
#include "OpenGL.hpp"

namespace nart {
  
    std::string Renderer::getDescription() {
        return "OpenGL Renderer";
    }
    
    void Renderer::renderPass(const Ref<nart::RenderPass>& pass) {
        renderPasses.push_back(pass);
    }
    
    
    void Renderer::renderFrame() {
        
        int windowWidth, windowHeight;
        
        Ref<Window> swindow = window.lock();
        
        swindow->getWindowSize(windowWidth, windowHeight);
        
        for (auto& pass : renderPasses) {
            
            glViewport(0, 0, windowWidth, windowHeight);
            
            if (pass->isNeedsClearColor()) {
                const float* clearColor = pass->getClearColor();
                glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
            }
            GLenum clearFlags = 0;
            if (pass->isNeedsClearColor()) {
                clearFlags |= GL_COLOR_BUFFER_BIT;
            }
            if (pass->isNeedsClearDepth()) {
                clearFlags |= GL_DEPTH_BUFFER_BIT;
            }
            if (clearFlags != 0) {
                glClear(clearFlags);
            }
            
            for (auto& dc : pass->getDrawCalls()) {
                glUseProgram(dc.shaderProgram->getID());
                
                int activeTexture = 0;
                GLenum activeTextureID = GL_TEXTURE0;
                
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
                        case DrawConstantsBlock::Item::Type::Texture2D:
                            glActiveTexture(activeTextureID);
                            glBindTexture(GL_TEXTURE_2D, constant.texture2d->getID());
                            glEnable(GL_TEXTURE_2D);
                            glUniform1i(constant.binding, activeTexture);
                            activeTexture += 1;
                            activeTextureID += 1;
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
