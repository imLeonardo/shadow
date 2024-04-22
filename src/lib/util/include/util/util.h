#ifndef SHADOW_UTIL_H
#define SHADOW_UTIL_H

#include "log/interface.h"

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define SHADOW_API __declspec(dllexport)
#      else
#        define SHADOW_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define SHADOW_API
#   endif // !WIN32
# else
#    define SHADOW_API
# endif // !SHARED_LIB

// 工具
namespace util {
    template<class T>
    inline int SHADOW_API ArrayLength(const T &array) {
        return sizeof(array) / sizeof(array[0]);
    }

    template<class T>
    bool SHADOW_API SetValue(const T *src, const T *value, const T *defaultValue) {
        if(value == nullptr)
            src = defaultValue;
        else
            src = value;
        return true;
    }
} // namespace util

#endif // !SHADOW_UTIL_H
