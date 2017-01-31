#include <nart/Exception.hpp>

namespace nart {
    
    Exception::Exception(std::string error) {
        this->error = error;
    }
    
}
