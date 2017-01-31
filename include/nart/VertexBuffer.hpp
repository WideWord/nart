#pragma once

#include <nart/Typedef.hpp>

#define NART_MAX_VERTEX_COMPONENTS 8

namespace nart {
    
    struct VertexFormat {
        struct Component {
            struct Type {
                enum Enum {
                    Float = 1
                };
            };
            uint16_t dimensions;
            Type::Enum type;
        };
        Component components[NART_MAX_VERTEX_COMPONENTS];
        uint16_t componentsCount;
    };
    
    
    
    class VertexBuffer {
    public:
        struct Description {
            VertexFormat vertexFormat;
            bool isImmutable;
        };
    private:
        uint32_t id;
        uint32_t indiciesID;
        uint32_t vao;
        Description description;
    public:
        VertexBuffer(const Description& description);
        ~VertexBuffer();
        void uploadData(void* data, size_t size, uint32_t* indicies, size_t indiciesSize);
        
        inline uint32_t getVAO() const { return vao; }
    };
    
}
