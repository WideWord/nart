#pragma once

#include <vector>
#include <nart/Typedef.hpp>
#include <nart/ShaderProgram.hpp>
#include <nart/DrawConstants.hpp>
#include <memory>

namespace nart {
    
    class VertexArray;
    class Renderer;
    
    struct DrawCallOptions {
        
        bool blendingEnabled = false;
        
        struct BlengingFactor {
            enum Enum {
                Zero = 0, One, SrcAlpha, OneMinusSrcAlpha, DstAlpha, OneMinusDstAlpha, ConstantColor
            };
        };
        
        BlengingFactor::Enum sourceBlendingFactor = BlengingFactor::SrcAlpha;
        BlengingFactor::Enum destinationBlendingFactor = BlengingFactor::OneMinusSrcAlpha;
        
        struct FaceCulling {
            enum Enum {
                NoCulling = 0,
                CullBack = 1,
                CullFront = 2
            };
        };
        FaceCulling::Enum faceCulling = FaceCulling::CullBack;
        
        bool depthTestEnabled = true;
        bool scissorTestEnabled = false;
        
        int scissorX = 0;
        int scissorY = 0;
        int scissorWidth = 0;
        int scissorHeight = 0;
        
        uint32_t primitivesRangeStart = 0;
        uint32_t primitivesRangeEnd = 0;
        
        DrawCallOptions() {}
    };
        
    class RenderPass {
    protected:
        struct DrawCall {
            Ref<VertexArray> vertexBuffer;
            Ref<ShaderProgram> shaderProgram;
            DrawConstants constants;
            DrawCallOptions options;
        };
        struct Options {
            bool needsClearColor = true;
            bool needsClearDepth = true;
            float clearColor[4];
            
            Options() {
                clearColor[0] = 0;
                clearColor[1] = 0;
                clearColor[2] = 0;
                clearColor[3] = 1;
            }
        };
    private:
        std::vector<DrawCall> drawCalls;
        Options options;
    protected:
        friend class Renderer;
        const std::vector<DrawCall>& getDrawCalls() const { return drawCalls; }
    public:
        
        void clear();
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawConstants& constants, const DrawCallOptions& options);
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram) {
            draw(vertexBuffer, shaderProgram, nart::DrawConstants(), nart::DrawCallOptions());
        }
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawConstants& constants) {
            draw(vertexBuffer, shaderProgram, constants, nart::DrawCallOptions());
        }
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawCallOptions& options) {
            draw(vertexBuffer, shaderProgram, nart::DrawConstants(), options);
        }
        
        const Options& getOptions() const { return options; }
        void setOptions(const Options& o) { options = o; }
    };
    
}
