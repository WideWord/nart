#include <nart/VertexBuffer.hpp>
#include "OpenGL.hpp"

namespace nart {

    VertexBuffer::VertexBuffer(const Description& desc) {
        description = desc;
        glGenBuffers(1, &id);
        glGenVertexArrays(1, &vao);
    }
    
    VertexBuffer::~VertexBuffer() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &id);
    }
    
    void VertexBuffer::uploadData(void* data, size_t size) {
        glBindBuffer(GL_VERTEX_ARRAY, id);
        glBufferData(GL_VERTEX_ARRAY, size, data, description.isImmutable ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        
        glBindVertexArray(vao);
        
        int stride = 0;
        
        for (int i = 0; i < description.vertexFormat.componentsCount; ++i) {
            GLenum type;
            size_t typeSize;
            switch (description.vertexFormat.components[i].type) {
            case VertexFormat::Component::Type::Float:
                type = GL_FLOAT;
                typeSize = sizeof(float);
                break;
            }
            glVertexAttribPointer(i, description.vertexFormat.components[i].dimensions, type, GL_FALSE, stride, 0);
            stride += typeSize * description.vertexFormat.components[i].dimensions;
        }
        
        glBindVertexArray(0);
        glBindBuffer(GL_VERTEX_ARRAY, 0);
    }
    
}
