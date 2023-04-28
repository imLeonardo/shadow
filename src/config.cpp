#include <memory>

#include "config.h"

#include "util/util.h"
#include "luabridge/luabridge.h"

namespace shadow {
    Config::Config(Token) {
    }

    void Config::readConfigFile(const char *configFile) {
        if(configFile == nullptr) {
            throw std::runtime_error("readConfigFile:config file is null");
        }
        auto luaObj = std::make_shared<luabridge::LuaObj>();
        luaObj->loadFile("script/lua/load_configfile.lua");
        auto config = luaObj->callFunc<luabridge::LuaRef>("loadFile", configFile);
        this->setLocale(config["locale"].cast<const char *>());
        this->setLogLevel((shadow::LogLevel) config["logLevel"].cast<int>());
        this->setThreadNum(config["threadNum"].cast<int>());
    }

    const char *Config::getLocale() {
        return this->locale;
    }

    bool Config::setLocale(const char *locale) {
        return util::setValue(this->locale, locale, "en_US.UTF-8");
    }

    shadow::LogLevel &Config::getLogLevel() {
        return this->logLevel;
    }

    void Config::setLogLevel(shadow::LogLevel level) {
        this->logLevel = level;
    }

    int &Config::getThreadNum() {
        return this->threadNum;
    }

    void Config::setThreadNum(int num) {
        this->threadNum = num;
    }

    void Config::print() {
        shadow::Log::info(
                "config locale:{},logLevel:{},threadNum:{}",
                this->getLocale(),
                (int) this->getLogLevel(),
                this->getThreadNum()
        );
    }
} // namespace shadow
