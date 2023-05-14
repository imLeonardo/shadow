#include <memory>

#include "configure/configure.h"

#include "log/interface.h"
#include "util/util.h"
#include "luabridge/luabridge.h"

namespace shadow {
    Configure::Configure(Singleton<Configure>::Token): mObj(nullptr), mConfig(nullptr) {

    }

    void Configure::init(const char *configFilePath) {
        if(configFilePath == nullptr) {
            throw std::runtime_error("Configure file is null");
        }
        this->mObj = std::make_shared<luabridge::LuaObj>();
        this->mObj->loadFile("script/lua/load_configfile.lua");
        this->mObj->callFunc<luabridge::LuaRef>("loadFile", configFilePath);
//        this->mConfig = std::make_shared<luabridge::LuaRef>(mObj->callFunc<luabridge::LuaRef>("getConfig", configFilePath));
        this->mConfig = mObj->callFunc<luabridge::LuaRef>("getConfig");
    }

    void Configure::print() {
        this->mObj->callFunc<luabridge::LuaRef>("printConfig");
    }

    int Configure::getInt(const char *key) {
        return this->mConfig[key].cast<int>();
    }

    const char *Configure::getString(const char *key) {
        return this->mConfig[key].cast<const char *>();
    }
} // namespace shadow
