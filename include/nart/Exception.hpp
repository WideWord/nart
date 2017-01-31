#pragma once

#include <exception>
#include <string>

namespace nart {
    
    class Exception {
    private:
        std::string error;
    public:
        Exception(std::string error);
        inline std::string getError() { return error; }
    };
    
}
