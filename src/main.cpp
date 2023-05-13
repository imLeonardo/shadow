#include <cstdlib>
#include <csignal>

#include "configure/configure_interface.h"
#include "log/log_interface.h"
#include "app.h"
#include "thread/pool.h"
#include "net/net_interface.h"

void signalHandler(int sig) {
    switch(sig) {
        case SIGINT:
            try {
                shadow::App::instance().stop();
            } catch(const std::exception &err) {
                shadow::log::critical(err.what());
            }
            break;
        case SIGSEGV:
            shadow::log::critical("segment violation");
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
        shadow::log::init();

        if(argc <= 1) {
            shadow::log::error("please input config file");
            return EXIT_FAILURE;
        }

        initSignalHandler();

        shadow::config::init(argv[1]);

//        std::locale::global(std::locale(shadow::config::getLocale()));
//
//        shadow::log::setLogLevel(shadow::config::getLogLevel());
//
//        shadow::thread::Pool::instance().createThread(shadow::config::getThreadNum());

//        shadow::net::Epoll::instance();

        shadow::App::instance().init();
        shadow::App::instance().start();
        shadow::App::instance().run();
        shadow::App::instance().exit();

//        shadow::net::Epoll::instance().release();

        shadow::thread::Pool::instance().release();
    } catch(const std::exception &err) {
        shadow::log::critical(err.what());
    }

    shadow::log::release();

    return EXIT_SUCCESS;
}
