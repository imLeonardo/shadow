#include <cstdlib>
#include <csignal>

#include "configure/interface.h"
#include "log/interface.h"
#include "app.h"
#include "threadpool/interface.h"
#include "net/interface.h"

void SignalHandler(int sig) {
    switch(sig) {
        case SIGINT:
            try {
                shadow::App::Instance().Stop();
            } catch(const std::exception &err) {
                shadow::log::Critical(err.what());
            }
            break;
        case SIGSEGV:
            shadow::log::Critical("segment violation");
            break;
        default:
            break;
    }
}

void InitSignalHandler() {
    signal(SIGINT, SignalHandler);
    signal(SIGSEGV, SignalHandler);
}

int main(int argc, char *argv[]) {
    try {
        ErrCode ret = shadow::log::Init();
        if(ret != ErrCode::SUCCESS) {
            return EXIT_FAILURE;
        }

        if(argc <= 1) {
            shadow::log::Error("please input config file");
            return EXIT_FAILURE;
        }

        InitSignalHandler();

        shadow::config::init(argv[1]);

        std::locale::global(std::locale(shadow::config::getString("locale")));

        shadow::log::setLogLevel(shadow::config::getInt("loglevel"));

        shadow::threadpool::createThread(10);//shadow::config::getInt("threadnum"));

        shadow::App::Instance().init();
        shadow::App::Instance().start();
        shadow::App::Instance().run();
        shadow::App::Instance().exit();

        shadow::threadpool::release();
    } catch(const std::exception &err) {
        shadow::log::Critical(err.what());
    }

    shadow::log::release();

    return EXIT_SUCCESS;
}
