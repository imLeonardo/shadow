#ifndef SHADOW_EPOLL_H
#define SHADOW_EPOLL_H

//#include <netinet/in.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <sys/epoll.h>
//#include <unistd.h>
#include <sys/types.h>

#include "define.h"
#include "singleton.h"

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

namespace shadow {
    namespace net {
        class DLL_API Epoll final : public shadow::Singleton<Epoll> {
        public:
            explicit Epoll(Token);

            ~Epoll() noexcept override;

            bool ctl(int fd, bool read, bool ctl);

            void release() const;
        private:
            int epollFd;
//            struct epoll_event ev;
        };
    }
} // namespace shadow

#endif // !SHADOW_EPOLL_H
