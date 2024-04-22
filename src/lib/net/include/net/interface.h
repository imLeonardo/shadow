#ifndef SHADOW_NET_INTERFACE_H
#define SHADOW_NET_INTERFACE_H

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

namespace shadow {
    namespace net {
        SHADOW_API void Init();
    }
}

#endif //SHADOW_INTERFACE_H
