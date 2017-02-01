#include "ShaderProgram.hpp"
#include <vector>
#include "Exception.hpp"
#include "Typedef.hpp"
#include "OpenGL.hpp"


namespace nart {
    
    Shader::Shader(const char* source, Type::Enum type) {
        GLenum shaderType;
        switch (type) {
            case Type::Vertex:
                shaderType = GL_VERTEX_SHADER; break;
            case Type::Fragment:
                shaderType = GL_FRAGMENT_SHADER; break;
        }
        id = glCreateShader(shaderType);
        GLint len = strlen(source);
        glShaderSource(id, 1, &source, (&len));
        glCompileShader(id);
        
        GLint isCompiled = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
            
            throw Exception(MakeString() << (char*)&(*errorLog.begin()));
        }
    }
    
    Shader::~Shader() {
        glDeleteShader(id);
    }
 
    ShaderProgram::ShaderProgram(const Ref<Shader>& vertexShader, const Ref<Shader>& fragmentShader) {
        id = glCreateProgram();
        glAttachShader(id, vertexShader->getID());
        glAttachShader(id, fragmentShader->getID());
        glLinkProgram(id);
        
        GLint isLinked = 0;
        glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            
            throw Exception(MakeString() << (char*)&(*infoLog.begin()));
        }
        
        glUseProgram(id);
        glValidateProgram(id);
        GLint isValid = 0;
        glGetProgramiv(id, GL_VALIDATE_STATUS, (int *)&isValid);
        if (isValid == GL_TRUE) {
            GLint maxLength = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            
            throw Exception(MakeString() << (char*)&(*infoLog.begin()));
        }
        
    }
    
    ShaderProgram::UniformBinding ShaderProgram::getUniformBinding(const char* name) {
        return glGetUniformLocation(id, name);
    }
    
    ShaderProgram::VertexComponentBinding ShaderProgram::getVertexComponentBinding(const char* name) {
        return glGetAttribLocation(id, name);
    }
    
    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(id);
    }
    
}
