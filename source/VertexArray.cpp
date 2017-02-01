#include <nart/VertexArray.hpp>
#include "OpenGL.hpp"

namespace nart {

    VertexArray::VertexArray(const Description& desc) {
        description = desc;
        glGenBuffers(1, &id);
        glGenBuffers(1, &indiciesID);
        glGenVertexArrays(1, &vao);
        
        
        
    }
    
    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &id);
    }
    
    void VertexArray::uploadData(void* data, size_t size, void* indicies, size_t indiciesSize) {
        indiciesCount = indiciesSize / description.indexSize;
        
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, description.isImmutable ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesSize, indicies, description.isImmutable ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesID);
        
        size_t offset = 0;
        size_t stride = 0;
        
        for (int i = 0; i < description.vertexFormat.componentsCount; ++i) {
            size_t typeSize;
            switch (description.vertexFormat.components[i].type) {
                case VertexFormat::Component::Type::Float: typeSize = sizeof(float); break;
                case VertexFormat::Component::Type::UnsignedByte: typeSize = sizeof(unsigned char); break;
            }
            stride += typeSize * description.vertexFormat.components[i].dimensions;
        }
        
        for (int i = 0; i < description.vertexFormat.componentsCount; ++i) {
            auto& component = description.vertexFormat.components[i];
            GLenum type;
            size_t typeSize;
            switch (description.vertexFormat.components[i].type) {
                case VertexFormat::Component::Type::Float:
                    type = GL_FLOAT;
                    typeSize = sizeof(float);
                    break;
                case VertexFormat::Component::Type::UnsignedByte:
                    type = GL_UNSIGNED_BYTE;
                    typeSize = sizeof(unsigned char);
            }
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, component.dimensions, type, component.normalize ? GL_TRUE : GL_FALSE, stride, (void*)offset);
            offset += typeSize * component.dimensions;
        }
        
        glBindVertexArray(0);
        
    }
    
}
