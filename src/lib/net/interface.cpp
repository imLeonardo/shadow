#include "net/interface.h"

#include "net/socket.h"

namespace shadow {
    namespace net {
        SHADOW_API void init() {
            shadow::net::Socket::Instance();
        }
    }
}
