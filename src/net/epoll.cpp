#include "net/epoll.h"

namespace shadow {
    namespace net {
        Epoll::Epoll(Token) { //: epoll_fd(epoll_create(1024)) {
            if(this->epollFd == -1) {
                throw std::runtime_error("epoll create fail");
            }
//            this->ev.data.fd;
        }

        Epoll::~Epoll() noexcept {
//            if(this->epoll_fd != -1)
//                close(this->epoll_fd);
        }

        bool Epoll::ctl(int fd, bool read, bool ctl) {
//            epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, fd, &this->ev);
            return true;
        }

        void Epoll::release() const {
//            if(this->epoll_fd != -1)
//                close(this->epoll_fd);
        }
    }
} // namespace shadow
