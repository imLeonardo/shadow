#include "net/interface.h"

#include "net/socket.h"

namespace shadow {
    namespace net {
        SHADOW_API void Init() {
            shadow::net::Socket::Instance();
        }
    }
}
