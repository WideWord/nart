#include <nart/RenderPass.hpp>

namespace nart {
    
    void RenderPass::clear() {
        drawCalls.clear();
    }
    
    void RenderPass::draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawConstants& constants, const DrawCallOptions &options) {
        DrawCall dc;
        dc.vertexBuffer = vertexBuffer;
        dc.shaderProgram = shaderProgram;
        dc.constants = constants;
        dc.options = options;
        drawCalls.push_back(dc);
    }
    
}
