#ifndef SHADOW_SOCKET_H
#define SHADOW_SOCKET_H

#include "singleton/singleton.h"
#include "log/interface.h"
#include "asio.hpp"

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
        class Socket final: public shadow::Singleton<Socket> {
        public:
            explicit Socket(Singleton<Socket>::Token);
        };
    }
}

#endif //SHADOW_SOCKET_H
