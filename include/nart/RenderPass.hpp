#pragma once

#include <vector>
#include "Typedef.hpp"
#include "ShaderProgram.hpp"
#include "DrawConstants.hpp"
#include <memory>

namespace nart {
    
    class VertexArray;
    class Renderer;
    
    struct Brush {
        
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
        
        Brush() {}
    };
        
    class RenderPass {
    protected:
        struct DrawCall {
            Ref<VertexArray> vertexBuffer;
            Ref<ShaderProgram> shaderProgram;
            DrawConstants constants;
            Brush brush;
            uint32_t primitivesRangeStart = 0;
            uint32_t primitivesRangeEnd = 0;
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
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawConstants& constants, const Brush& brush, int primitivesRangeStart = 0, int primitivesRangeEnd = 0);
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram) {
            draw(vertexBuffer, shaderProgram, nart::DrawConstants(), nart::Brush());
        }
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawConstants& constants) {
            draw(vertexBuffer, shaderProgram, constants, nart::Brush());
        }
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const Brush& brush) {
            draw(vertexBuffer, shaderProgram, nart::DrawConstants(), brush);
        }
        
        const Options& getOptions() const { return options; }
        void setOptions(const Options& o) { options = o; }
    };
    
}
