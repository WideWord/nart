#include "Renderer.hpp"
#include "RenderPass.hpp"
#include "Texture2D.hpp"
#include "System.hpp"
#include "OpenGL.hpp"

namespace nart {
    
    GLenum getGLBlendingFactor(Brush::BlengingFactor::Enum factor) {
        switch (factor) {
            case Brush::BlengingFactor::Zero: return GL_ZERO;
            case Brush::BlengingFactor::One: return GL_ONE;
            case Brush::BlengingFactor::SrcAlpha: return GL_SRC_ALPHA;
            case Brush::BlengingFactor::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
            case Brush::BlengingFactor::DstAlpha: return GL_DST_ALPHA;
            case Brush::BlengingFactor::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
            case Brush::BlengingFactor::ConstantColor : return GL_CONSTANT_COLOR;
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
        
        Ref<System> swindow = system.lock();
        
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
                                
                if (dc.brush.blendingEnabled) {
                    glEnable(GL_BLEND);
                    glBlendFunc(getGLBlendingFactor(dc.brush.sourceBlendingFactor), getGLBlendingFactor(dc.brush.destinationBlendingFactor));
                    glBlendEquation(GL_FUNC_ADD);
                } else {
                    glDisable(GL_BLEND);
                }
                
                switch (dc.brush.faceCulling) {
                    case Brush::FaceCulling::NoCulling:
                        glDisable(GL_CULL_FACE);
                        break;
                    case Brush::FaceCulling::CullBack:
                        glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);
                        break;
                    case Brush::FaceCulling::CullFront:
                        glEnable(GL_CULL_FACE);
                        glCullFace(GL_FRONT);
                        break;
                }
                
                if (dc.brush.depthTestEnabled) {
                    glEnable(GL_DEPTH_TEST);
                } else {
                    glDisable(GL_DEPTH_TEST);
                }
                
                if (dc.brush.scissorTestEnabled) {
                    glEnable(GL_SCISSOR_TEST);
                    glScissor(dc.brush.scissorX, dc.brush.scissorY, dc.brush.scissorWidth, dc.brush.scissorHeight);
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
                if (dc.primitivesRangeEnd == 0) {
                    indiciesCount = dc.vertexBuffer->getIndiciesCount() - dc.primitivesRangeStart;
                } else {
                    indiciesCount = dc.primitivesRangeEnd - dc.primitivesRangeStart;
                }
                
                glDrawElements(GL_TRIANGLES, indiciesCount, indexSize, (void*)(dc.primitivesRangeStart * dc.vertexBuffer->getDescription().indexSize));
            }
            
            pass->clear();
        }
        renderPasses.clear();
        
        
    }

}
