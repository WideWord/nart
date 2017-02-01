#pragma once

#include "Typedef.hpp"
#include "VertexFormat.hpp"


namespace nart {
    
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
