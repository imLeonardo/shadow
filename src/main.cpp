#include <cstdlib>
#include <csignal>

#include "configure/interface.h"
#include "log/interface.h"
#include "app.h"
#include "threadpool/interface.h"
#include "net/interface.h"

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
        ErrCode ret = shadow::log::init();
        if(ret != ErrCode::SUCCESS) {
            return EXIT_FAILURE;
        }

        if(argc <= 1) {
            shadow::log::error("please input config file");
            return EXIT_FAILURE;
        }

        initSignalHandler();

        shadow::config::init(argv[1]);

        std::locale::global(std::locale(shadow::config::getString("locale")));

        shadow::log::setLogLevel(shadow::config::getInt("loglevel"));

        shadow::threadpool::createThread(10);//shadow::config::getInt("threadnum"));

        shadow::App::instance().init();
        shadow::App::instance().start();
        shadow::App::instance().run();
        shadow::App::instance().exit();

        shadow::threadpool::release();
    } catch(const std::exception &err) {
        shadow::log::critical(err.what());
    }

    shadow::log::release();

    return EXIT_SUCCESS;
}
