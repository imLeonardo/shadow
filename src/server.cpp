#include "server.h"

#include <numeric>
#include <map>
#include <stack>
#include <thread>

//#include "configure.h"
#include "log/log.h"
#include "util/util.h"
#include "thread/pool.h"
#include "net/epoll.h"
#include "map/map.h"

namespace shadow {
    Server::Server(Token) : serverState(ServerState::UNDEFINED) {

    }

    /*
    * 初始化
    * @return errcode
    */
    ErrCode Server::init() {
        shadow::Log::info("server init");
        this->setServerState(ServerState::INIT);

        return ErrCode::SUCCESS;
    }

    /*
    * 启动
    * @return errcode
    */
    ErrCode Server::start() {
        shadow::Log::info("server start");
        this->setServerState(ServerState::START);

        return ErrCode::SUCCESS;
    }

    /*
    * 运行
    * @return errcode
    */
    ErrCode Server::run() {
        shadow::Log::info("server begin run");
        this->setServerState(ServerState::RUN);

        shadow::thread::Pool::instance().addTask("create map", []() {
            auto *test_map = new shadow::Map();
            test_map->createMap(160, 35, 0);

            ErrCode e = shadow::MapPath::instance().aStar(test_map);
            shadow::Log::info("aStar:{}", (int) e);
//            test_map->print_map();
        });

        for(int i = 0; i < 10; i++) {
            shadow::thread::Pool::instance().addTask("add work thread", [this, &i]() {
//                this->m_luaobjs.insert(std::make_pair<int, luabridge::luaobj>(i, luabridge::luaobj()));
//                this->m_luaobjs.at(i).loadfile("script/lua/test1.lua");
//                auto ret = this->m_luaobjs.at(i).call_func<luabridge::LuaRef>("test_add");
                this->luaObjs.insert(std::make_pair<int, luabridge::LuaObj *>(std::move(i), new luabridge::LuaObj));
                while(Server::instance().isRunning()) {
                    int a[] = { 1, 2, 3, 4, 5 };
                    Log::info("a's length is {},n:{}", util::arrayLength(a), i);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            });
        }

        shadow::thread::Pool::instance().joinAll();

        return ErrCode::SUCCESS;
    }

    /*
    * 暂停
    * @return errcode
    */
    ErrCode Server::pause() {
        shadow::Log::info("server begin pause");
        this->setServerState(ServerState::PAUSE);

        return ErrCode::SUCCESS;
    }

    /*
    * 停止
    * @return errcode
    */
    ErrCode Server::stop() {
        shadow::Log::info("server begin stop");
        this->setServerState(ServerState::STOP);

        std::map<int, luabridge::LuaObj*>::iterator it;
        for(it = this->luaObjs.begin(); it != this->luaObjs.end();) {
            delete it->second;
            this->luaObjs.erase(it++);
        }

        shadow::thread::Pool::instance().release();

        return ErrCode::SUCCESS;
    }

    /*
    * 退出
    * @return errcode
    */
    ErrCode Server::exit() noexcept {
        shadow::Log::info("server begin exit");

        return ErrCode::SUCCESS;
    }

    /*
    * 获取服务器状态
    * @return server_state
    */
    ServerState Server::getServerState() {
        return this->serverState;
    }

    /*
    * 设置服务器状态
    * @return errcode
    */
    ErrCode Server::setServerState(const ServerState &state) {
        shadow::Log::info("set server state {}", (int) state);
        this->serverState = state;

        return ErrCode::SUCCESS;
    }

    bool Server::isRunning() {
        return this->serverState == ServerState::RUN;
    }
} // namespace shadow
