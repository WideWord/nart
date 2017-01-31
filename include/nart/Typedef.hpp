#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <stdint.h>

namespace nart {
    
    template<typename T> using Ref = std::shared_ptr<T>;
    template<typename T> using WRef = std::weak_ptr<T>;
    
    template<typename T, typename R> inline Ref<T> RefCast(const Ref<R>& ref) { return std::move(std::static_pointer_cast<T>(ref)); };
    
    class MakeString {
    public:
        template<class T>
        inline MakeString& operator<< (const T& arg) {
            m_stream << arg;
            return *this;
        }
        inline operator std::string() const {
            return m_stream.str();
        }
    protected:
        std::stringstream m_stream;
    };
    
}
