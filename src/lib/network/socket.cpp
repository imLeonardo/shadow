#include "net/socket.h"

#include "singleton/singleton.h"
#include "log/interface.h"
#include "asio.hpp"

namespace shadow {
    namespace network {
        Socket::Socket(Singleton<Socket>::Token) {

        }
    }
}
