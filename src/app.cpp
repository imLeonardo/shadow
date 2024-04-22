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
    App::App(Singleton<App>::Token): mState(AppState::UNDEFINED) {

    }

    /*
    * 初始化
    * @return errcode
    */
    ErrCode App::Init() {
        shadow::log::info("server Init");
        this->setState(AppState::INIT);

        return ErrCode::SUCCESS;
    }

    /*
    * 启动
    * @return errcode
    */
    ErrCode App::Start() {
        shadow::log::info("server Start");
        this->setState(AppState::START);

        return ErrCode::SUCCESS;
    }

    /*
    * 运行
    * @return errcode
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

        for(int i = 0; i < 1; i++) {
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
        shadow::threadpool::joinAll();

        return ErrCode::SUCCESS;
    }

    /*
    * 暂停
    * @return errcode
    */
    ErrCode App::pause() {
        shadow::log::info("server pause");
        this->setState(AppState::PAUSE);

        return ErrCode::SUCCESS;
    }

    /*
* 暂停
* @return errcode
*/
    ErrCode App::resume() {
        shadow::log::info("server resume");
        this->setState(AppState::RUN);

        return ErrCode::SUCCESS;
    }

    /*
    * 停止
    * @return errcode
    */
    ErrCode App::Stop() {
        shadow::log::info("server begin Stop");
        this->setState(AppState::STOP);

        shadow::threadpool::Release();

        return ErrCode::SUCCESS;
    }

    /*
    * 退出
    * @return errcode
    */
    ErrCode App::Exit() noexcept {
        shadow::log::info("server begin Exit");

        return ErrCode::SUCCESS;
    }

    /*
    * 获取服务器状态
    * @return server_state
    */
    AppState App::getState() {
        return this->mState;
    }

    /*
    * 设置服务器状态
    * @return errcode
    */
    ErrCode App::setState(const AppState &state) {
        shadow::log::info("set app state:{}", (int) state);
        this->mState = state;

        return ErrCode::SUCCESS;
    }

    bool App::isRunning() {
        return this->mState == AppState::RUN;
    }
} // namespace shadow
