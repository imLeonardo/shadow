#ifndef SHADOW_UTIL_H
#define SHADOW_UTIL_H

#include "log/log.h"

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define DLL_API __declspec(dllexport)
#      else
#        define DLL_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define DLL_API
#   endif // !WIN32
# else
#    define DLL_API
# endif // !SHARED_LIB

// 工具
namespace util {
    template<class T>
    inline int DLL_API arrayLength(const T &array) {
        return sizeof(array) / sizeof(array[0]);
    }

    template<class T>
    bool DLL_API setValue(const T *src, const T *value, const T *defaultValue) {
        if(value == nullptr)
            src = defaultValue;
        else
            src = value;
        return true;
    }
} // namespace util

#endif // !SHADOW_UTIL_H
