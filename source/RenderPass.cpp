#include "RenderPass.hpp"

namespace nart {
    
    void RenderPass::clear() {
        drawCalls.clear();
    }
    
    void RenderPass::draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawConstants& constants, const Brush &brush, int primitivesRangeStart, int primitivesRangeEnd) {
        DrawCall dc;
        dc.vertexBuffer = vertexBuffer;
        dc.shaderProgram = shaderProgram;
        dc.constants = constants;
        dc.brush = brush;
        dc.primitivesRangeEnd = primitivesRangeStart;
        dc.primitivesRangeEnd = primitivesRangeEnd;
        drawCalls.push_back(dc);
    }
    
}
