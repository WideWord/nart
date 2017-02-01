#pragma once

#include <nart/Typedef.hpp>

namespace nart {
    
    class ShaderProgram;
    
    class Shader {
    public:
        struct Type {
            enum Enum {
                Vertex = 1,
                Fragment = 2
            };
        };
    private:
        uint32_t id;
        Type::Enum type;
    protected:
        friend class ShaderProgram;
        inline uint32_t getID() const {
            return id;
        }
    public:
        Shader(const char* source, Type::Enum type);
        ~Shader();
        inline Type::Enum getType() const {
            return type;
        }
    };
    
    class ShaderProgram {
    private:
        uint32_t id;
    public:
        ShaderProgram(const Ref<Shader>& vertexShader, const Ref<Shader>& fragmentShader);
        ~ShaderProgram();
        inline uint32_t getID() {
            return id;
        }
        
        using UniformBinding = int32_t;
        using VertexComponentBinding = int32_t;
        UniformBinding getUniformBinding(const char* name);
        VertexComponentBinding getVertexComponentBinding(const char* name);
    };
    
}
