#pragma once

#include <nart/Typedef.hpp>

namespace nart {
    
    class Texture2D {
    public:
        struct Format {
            enum Enum {
                RGBA = 1
            };
        };
        struct Description {
            int width;
            int height;
            Format::Enum format;
        };
    private:
        Description description;
        uint32_t id;
    public:
        Texture2D(const Description& description);
        ~Texture2D();
        
        void uploadImage(void* image);
        
        uint32_t getID() const { return id; }
    };
    
}
