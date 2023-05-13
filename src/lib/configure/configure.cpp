#include <memory>

#include "configure/configure.h"

#include "log/log_interface.h"
#include "util/util.h"
#include "luabridge/luabridge.h"

namespace shadow {
    Configure::Configure(Singleton<Configure>::Token) {

    }

    void Configure::init(const char *configFilePath) {
        if(configFilePath == nullptr) {
            throw std::runtime_error("Configure file is null");
        }
        this->mConfigFile = configFilePath;
        this->mObj = std::make_shared<luabridge::LuaObj>();
        this->mObj->loadFile("script/lua/load_configfile.lua");
    }

    void Configure::print() {
        this->mObj->callFunc<luabridge::LuaRef>("printConfig");
    }

    int Configure::getint(const char *key) {
        auto config = mObj->callFunc<luabridge::LuaRef>("getConfig", this->mConfigFile);
        return config[key].cast<int>();
    }

    const char *Configure::getstring(const char *key) {
        auto config = mObj->callFunc<luabridge::LuaRef>("getConfig", this->mConfigFile);
        return config[key].cast<const char *>();
    }
} // namespace shadow
