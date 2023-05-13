#include "net/socket.h"

#include "singleton/singleton.h"
#include "log/log_interface.h"
#include "asio.hpp"

namespace shadow {
    namespace net {
        Socket::Socket(Singleton<Socket>::Token) {

        }
    }
}
