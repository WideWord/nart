#pragma once

namespace nart {
    
#define NART_MAX_VERTEX_COMPONENTS 8
    
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
            return *this;
        }
    };
    
}
