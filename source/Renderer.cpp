#include <nart/Renderer.hpp>
#include <nart/RenderPass.hpp>
#include <nart/Texture2D.hpp>
#include <nart/Window.hpp>
#include "OpenGL.hpp"

namespace nart {
    
    GLenum getGLBlendingFactor(DrawCallOptions::BlengingFactor::Enum factor) {
        switch (factor) {
            case DrawCallOptions::BlengingFactor::Zero: return GL_ZERO;
            case DrawCallOptions::BlengingFactor::One: return GL_ONE;
            case DrawCallOptions::BlengingFactor::SrcAlpha: return GL_SRC_ALPHA;
            case DrawCallOptions::BlengingFactor::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
            case DrawCallOptions::BlengingFactor::DstAlpha: return GL_DST_ALPHA;
            case DrawCallOptions::BlengingFactor::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
            case DrawCallOptions::BlengingFactor::ConstantColor : return GL_CONSTANT_COLOR;
        }
    }
  
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
            
            auto passOptions = pass->getOptions();
            
            if (passOptions.needsClearColor) {
                glClearColor(passOptions.clearColor[0], passOptions.clearColor[1], passOptions.clearColor[2], passOptions.clearColor[3]);
            }
            GLenum clearFlags = 0;
            if (passOptions.needsClearColor) {
                clearFlags |= GL_COLOR_BUFFER_BIT;
            }
            if (passOptions.needsClearDepth) {
                clearFlags |= GL_DEPTH_BUFFER_BIT;
            }
            if (clearFlags != 0) {
                glDisable(GL_SCISSOR_TEST);
                glClear(clearFlags);
            }
            
            for (auto& dc : pass->getDrawCalls()) {
                glUseProgram(dc.shaderProgram->getID());
                
                int activeTexture = 0;
                GLenum activeTextureID = GL_TEXTURE0;
                
                for (auto& constant : dc.constants.getItems()) {
                    switch (constant.type) {
                        case DrawConstants::Item::Type::Float:
                            glUniform1fv(constant.binding, 1, constant.rawData.floatData); break;
                        case DrawConstants::Item::Type::Vector2:
                            glUniform2fv(constant.binding, 1, constant.rawData.floatData); break;
                        case DrawConstants::Item::Type::Vector3:
                            glUniform3fv(constant.binding, 1, constant.rawData.floatData); break;
                        case DrawConstants::Item::Type::Vector4:
                            glUniform4fv(constant.binding, 1, constant.rawData.floatData); break;
                        case DrawConstants::Item::Type::Matrix2:
                            glUniformMatrix2fv(constant.binding, 1, GL_FALSE, constant.rawData.floatData); break;
                        case DrawConstants::Item::Type::Matrix3:
                            glUniformMatrix3fv(constant.binding, 1, GL_FALSE, constant.rawData.floatData); break;
                        case DrawConstants::Item::Type::Matrix4:
                            glUniformMatrix4fv(constant.binding, 1, GL_FALSE, constant.rawData.floatData); break;
                        case DrawConstants::Item::Type::Texture2D:
                            glActiveTexture(activeTextureID);
                            glBindTexture(GL_TEXTURE_2D, constant.texture2d->getID());
                            glUniform1i(constant.binding, activeTexture);
                            activeTexture += 1;
                            activeTextureID += 1;
                            break;
                    }
                }
                                
                if (dc.options.blendingEnabled) {
                    glEnable(GL_BLEND);
                    glBlendFunc(getGLBlendingFactor(dc.options.sourceBlendingFactor), getGLBlendingFactor(dc.options.destinationBlendingFactor));
                    glBlendEquation(GL_FUNC_ADD);
                } else {
                    glDisable(GL_BLEND);
                }
                
                switch (dc.options.faceCulling) {
                    case DrawCallOptions::FaceCulling::NoCulling:
                        glDisable(GL_CULL_FACE);
                        break;
                    case DrawCallOptions::FaceCulling::CullBack:
                        glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);
                        break;
                    case DrawCallOptions::FaceCulling::CullFront:
                        glEnable(GL_CULL_FACE);
                        glCullFace(GL_FRONT);
                        break;
                }
                
                if (dc.options.depthTestEnabled) {
                    glEnable(GL_DEPTH_TEST);
                } else {
                    glDisable(GL_DEPTH_TEST);
                }
                
                if (dc.options.scissorTestEnabled) {
                    glEnable(GL_SCISSOR_TEST);
                    glScissor(dc.options.scissorX, dc.options.scissorY, dc.options.scissorWidth, dc.options.scissorHeight);
                } else {
                    glDisable(GL_SCISSOR_TEST);
                }
                
                glBindVertexArray(dc.vertexBuffer->getVAO());
                
                GLenum indexSize;
                switch (dc.vertexBuffer->getDescription().indexSize) {
                    case 1:
                        indexSize = GL_UNSIGNED_BYTE; break;
                    case 2:
                        indexSize = GL_UNSIGNED_SHORT; break;
                    case 4:
                        indexSize = GL_UNSIGNED_INT; break;
                    default:
                        indexSize = GL_UNSIGNED_INT; break;
                }
                
                uint32_t indiciesCount;
                if (dc.options.primitivesRangeEnd == 0) {
                    indiciesCount = dc.vertexBuffer->getIndiciesCount() - dc.options.primitivesRangeStart;
                } else {
                    indiciesCount = dc.options.primitivesRangeEnd - dc.options.primitivesRangeStart;
                }
                
                auto err = glGetError();
                glDrawElements(GL_TRIANGLES, indiciesCount, indexSize, (void*)(dc.options.primitivesRangeStart * dc.vertexBuffer->getDescription().indexSize));
            }
            
            pass->clear();
        }
        renderPasses.clear();
        
        
    }

}
