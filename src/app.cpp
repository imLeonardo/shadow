#include "app.h"

#include <numeric>
#include <map>
#include <stack>
#include <thread>

#include "configure/interface.h"
#include "log/interface.h"
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
    ErrCode App::init() {
        shadow::log::info("server init");
        this->setState(AppState::INIT);

        return ErrCode::SUCCESS;
    }

    /*
    * 启动
    * @return errcode
    */
    ErrCode App::start() {
        shadow::log::info("server start");
        this->setState(AppState::START);

        return ErrCode::SUCCESS;
    }

    /*
    * 运行
    * @return errcode
    */
    ErrCode App::run() {
        shadow::log::info("server begin run");
        this->setState(AppState::RUN);

//        shadow::thread::Pool::instance().addTask("create map", []() {
//            auto *test_map = new shadow::Map();
//            test_map->createMap(160, 35, 0);
//
//            ErrCode e = shadow::MapPath::instance().aStar(test_map);
//            shadow::log::info("aStar:{}", (int) e);
////            test_map->print_map();
//        });

        for(int i = 0; i < 10; i++) {
            shadow::threadpool::addTask("add work thread", [this, &i]() {
//                this->m_luaobjs.insert(std::make_pair<int, luabridge::luaobj>(i, luabridge::luaobj()));
//                this->m_luaobjs.at(i).loadfile("script/lua/test1.lua");
//                auto ret = this->m_luaobjs.at(i).call_func<luabridge::LuaRef>("test_add");
                this->mLuaObjs.insert(std::make_pair<int, luabridge::LuaObj *>(std::move(i), new luabridge::LuaObj));
                while(this->isRunning()) {
                    int a[] = {1, 2, 3, 4, 5};
                    shadow::log::info("a's length is {},n:{}", util::arrayLength(a), i);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
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
        shadow::log::info("server begin pause");
        this->setState(AppState::PAUSE);

        return ErrCode::SUCCESS;
    }

    /*
    * 停止
    * @return errcode
    */
    ErrCode App::stop() {
        shadow::log::info("server begin stop");
        this->setState(AppState::STOP);

        std::map<int, luabridge::LuaObj *>::iterator it;
        for(it = this->mLuaObjs.begin(); it != this->mLuaObjs.end();) {
            delete it->second;
            this->mLuaObjs.erase(it++);
        }

        shadow::threadpool::release();

        return ErrCode::SUCCESS;
    }

    /*
    * 退出
    * @return errcode
    */
    ErrCode App::exit() noexcept {
        shadow::log::info("server begin exit");

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
        shadow::log::info("set app state {}", (int) state);
        this->mState = state;

        return ErrCode::SUCCESS;
    }

    bool App::isRunning() {
        return this->mState == AppState::RUN;
    }
} // namespace shadow
