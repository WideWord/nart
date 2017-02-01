#include <nart/Texture2D.hpp>
#include "OpenGL.hpp"

namespace nart {
    
    Texture2D::Texture2D(const Description& desc) {
        description = desc;
        glGenTextures(1, &id);
        
        glBindTexture(GL_TEXTURE_2D, id);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
    }
    
    Texture2D::~Texture2D() {
        glDeleteTextures(1, &id);
    }
    
    void Texture2D::uploadImage(void* image) {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, description.width, description.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    
}
