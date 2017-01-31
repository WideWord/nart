#include <nart/VertexBuffer.hpp>
#include "OpenGL.hpp"

namespace nart {

    VertexBuffer::VertexBuffer(const Description& desc) {
        description = desc;
        glGenBuffers(1, &id);
        glGenBuffers(1, &indiciesID);
        glGenVertexArrays(1, &vao);
    }
    
    VertexBuffer::~VertexBuffer() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &id);
    }
    
    void VertexBuffer::uploadData(void* data, size_t size, uint32_t* indicies, size_t indiciesSize) {
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, description.isImmutable ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesSize, indicies, description.isImmutable ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        
        
        size_t offset = 0;
        
        size_t stride;
        
        for (int i = 0; i < description.vertexFormat.componentsCount; ++i) {
            size_t typeSize;
            switch (description.vertexFormat.components[0].type) {
                case VertexFormat::Component::Type::Float: typeSize = sizeof(float); break;
            }
            stride += typeSize * description.vertexFormat.components[i].dimensions;
        }
        
        for (int i = 0; i < description.vertexFormat.componentsCount; ++i) {
            GLenum type;
            size_t typeSize;
            switch (description.vertexFormat.components[i].type) {
            case VertexFormat::Component::Type::Float:
                type = GL_FLOAT;
                typeSize = sizeof(float);
                break;
            }
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, description.vertexFormat.components[i].dimensions, type, GL_FALSE, stride, (void*)offset);
            offset += typeSize * description.vertexFormat.components[i].dimensions;
        }
        
        glBindVertexArray(0);
    }
    
}
