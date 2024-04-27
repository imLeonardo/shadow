#include "app.h"

#include <numeric>
#include <map>
#include <stack>
#include <thread>

#include "configure/interface.h"
#include "log/interface.h"
#include "jsmanager/interface.h"
#include "util/util.h"
#include "threadpool/interface.h"
//#include "map/map.h"

namespace shadow {
    App::App(Singleton<App>::Token): mAppState(AppState::UNDEFINED) {

    }

    /*
    * 初始化
    * @return ErrCode
    */
    ErrCode App::Init() {
        shadow::log::info("server Init");
        this->setState(AppState::INIT);

        return ErrCode::SUCCESS;
    }

    /*
    * 启动
    * @return ErrCode
    */
    ErrCode App::Start() {
        shadow::log::info("server Start");
        this->setState(AppState::START);

        return ErrCode::SUCCESS;
    }

    /*
    * 运行
    * @return ErrCode
    */
    ErrCode App::Run() {
        shadow::log::info("server Run");
        this->setState(AppState::RUN);

//        shadow::thread::Pool::instance().addTask("create map", []() {
//            auto *test_map = new shadow::Map();
//            test_map->createMap(160, 35, 0);
//
//            ErrCode e = shadow::MapPath::instance().aStar(test_map);
//            shadow::log::info("aStar:{}", (int) e);
////            test_map->print_map();
//        });

        for(uint32_t i = 0; i < 1; i++) {
            shadow::threadpool::addTask("add work thread", [this, &i]() {
                while(this->isRunning()) {
//                    int a[] = {1, 2, 3, 4, 5};
//                    shadow::log::info("a's length is {},n:{}", util::arrayLength(a), i);

                    shadow::js::Context jsContext = shadow::js::CreateContext();
                    JSValue jsValue = jsContext.EvalFile("script/main.js");
                    if (JS_IsException(jsValue)) {
                        shadow::log::error("JS_Eval Error jsfile:{}", "script/main.js");
                        return ErrCode::FAIL;
                    }
                    JS_FreeValue(jsContext.GetContext(), jsValue);

                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                return ErrCode::SUCCESS;
            });
        }
        shadow::threadpool::JoinAll();

        return ErrCode::SUCCESS;
    }

    /*
    * 暂停
    * @return ErrCode
    */
    ErrCode App::pause() {
        shadow::log::info("server pause");
        this->setAppState(AppState::PAUSE);

        return ErrCode::SUCCESS;
    }

    /*
    * 暂停
    * @return ErrCode
    */
    ErrCode App::resume() {
        shadow::log::info("server resume");
        this->setAppState(AppState::RUN);

        return ErrCode::SUCCESS;
    }

    /*
    * 停止
    * @return ErrCode
    */
    ErrCode App::Stop() {
        shadow::log::info("server begin Stop");
        this->setState(AppState::STOP);

        shadow::threadpool::Release();

        return ErrCode::SUCCESS;
    }

    /*
    * 退出
    * @return ErrCode
    */
    ErrCode App::Exit() noexcept {
        shadow::log::info("server begin Exit");

        return ErrCode::SUCCESS;
    }

    /*
    * 获取服务器状态
    * @return AppState
    */
    AppState App::getAppState() {
        return this->mAppState;
    }

    /*
    * 设置服务器状态
    * @return ErrCode
    */
    ErrCode App::setAppState(const AppState &appState) {
        shadow::log::info("set app state:{}", static_cast<uint32_t>(appState));
        this->mAppState = appState;

        return ErrCode::SUCCESS;
    }

    bool App::isRunning() {
        return this->mAppState == AppState::RUN;
    }
} // namespace shadow
