#pragma once

#include <nart/Typedef.hpp>

#define NART_MAX_VERTEX_COMPONENTS 8

namespace nart {
    
    struct VertexFormat {
        struct Component {
            struct Type {
                enum Enum {
                    Float = 1,
                    UnsignedByte = 2
                };
            };
            uint16_t dimensions;
            Type::Enum type;
            bool normalize = false;
            
            Component() {}
        };
        VertexFormat() {}
        
        Component components[NART_MAX_VERTEX_COMPONENTS];
        uint16_t componentsCount = 0;
        
        VertexFormat& Float() {
            components[componentsCount].dimensions = 1;
            components[componentsCount].type = Component::Type::Float;
            componentsCount += 1;
            return *this;
        }
        
        VertexFormat& Vector2() {
            components[componentsCount].dimensions = 2;
            components[componentsCount].type = Component::Type::Float;
            componentsCount += 1;
            return *this;
        }
        
        VertexFormat& Vector3() {
            components[componentsCount].dimensions = 3;
            components[componentsCount].type = Component::Type::Float;
            componentsCount += 1;
            return *this;
        }
        
        VertexFormat& Vector4() {
            components[componentsCount].dimensions = 4;
            components[componentsCount].type = Component::Type::Float;
            componentsCount += 1;
            return *this;
        }
        VertexFormat& Vector4UByte() {
            components[componentsCount].dimensions = 4;
            components[componentsCount].type = Component::Type::UnsignedByte;
            componentsCount += 1;
            return *this;
        }
        
        VertexFormat& normalized() {
            components[componentsCount - 1].normalize = true;
        }
    };
    
    
    
    class VertexArray {
    public:
        struct Description {
            VertexFormat vertexFormat;
            bool isImmutable = false;
            uint8_t indexSize = 4;
            
            Description() {}
        };
    private:
        uint32_t id;
        uint32_t indiciesID;
        uint32_t vao;
        
        uint32_t indiciesCount;
        
        Description description;
    public:
        VertexArray(const Description& description);
        ~VertexArray();
        void uploadData(void* data, size_t size, void* indicies, size_t indiciesSize);
        
        inline uint32_t getVAO() const { return vao; }
        inline uint32_t getIndiciesCount() const { return indiciesCount; }
        inline const Description& getDescription() const { return description; }
    };
    
}
