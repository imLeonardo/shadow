#include <cstdlib>
#include <csignal>

#include "config.h"
#include "server.h"
#include "thread/pool.h"
#include "net/epoll.h"

void signalHandler(int sig) {
    switch(sig) {
        case SIGINT:
            try {
                shadow::Server::instance().stop();
            } catch(const std::exception &err) {
                shadow::Log::critical(err.what());
            }
            break;
        case SIGSEGV:
            shadow::Log::critical("segment violation");
            break;
        default:
            break;
    }
}

void initSignalHandler() {
    signal(SIGINT, signalHandler);
    signal(SIGSEGV, signalHandler);
}

int main(int argc, char *argv[]) {
    try {
        shadow::Log::init();

        if(argc <= 1) {
            shadow::Log::error("please input config file");
            return EXIT_FAILURE;
        }

        initSignalHandler();

        shadow::Config::instance().readConfigFile(argv[1]);

        std::locale::global(std::locale(shadow::Config::instance().getLocale()));

        shadow::Log::setLogLevel(shadow::Config::instance().getLogLevel());

        shadow::thread::Pool::instance().createThread(shadow::Config::instance().getThreadNum());

        shadow::net::Epoll::instance();

        shadow::Server::instance().init();
        shadow::Server::instance().start();
        shadow::Server::instance().run();
        shadow::Server::instance().exit();

        shadow::net::Epoll::instance().release();

        shadow::thread::Pool::instance().release();
    } catch(const std::exception &err) {
        shadow::Log::critical(err.what());
    }

    shadow::Log::release();

    return EXIT_SUCCESS;
}
