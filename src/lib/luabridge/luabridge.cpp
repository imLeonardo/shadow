#include "luabridge/luabridge.h"

#include "log/interface.h"

namespace luabridge {
    LuaObj::LuaObj(): mLuaState(luaL_newstate()), mTopIndex(0) {
        shadow::log::init();
        shadow::log::debug("luaobj");
        luaL_openlibs(this->mLuaState);
    }

    LuaObj::~LuaObj() {
        shadow::log::debug("~luaobj");
        shadow::log::release();
        if(this->mLuaState != nullptr) {
            lua_close(this->mLuaState);
            this->mLuaState = nullptr;
        }
    }

    bool LuaObj::loadFile(const char *filePath) {
        int ret = luaL_dofile(this->mLuaState, filePath);
        if(ret != LUA_OK) {
            throw std::runtime_error("luaobj load file error,file:"
                                     + std::string(filePath)
                                     + ",error:" + lua_tostring(this->mLuaState, -1));
        }
        return true;
    }

    luabridge::LuaRef LuaObj::doString(const char *) {
        return LuaRef::fromStack(this->mLuaState);
    }
} // namespace luabridge

static int logTrace(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::log::trace(s);
    return 1;
}

static int logDebug(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::log::debug(s);
    return 1;
}

static int logInfo(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::log::info(s);
    return 1;
}

static int logWarn(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::log::warn(s);
    return 1;
}

static int logError(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::log::error(s);
    return 1;
}

static int logCritical(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::log::critical(s);
    return 1;
}

int luaopen_luabridge_clog(lua_State *luaState) {
    luaL_checkversion(luaState);
    const luaL_Reg l[] = {
            {"trace",    logTrace},
            {"debug",    logDebug},
            {"info",     logInfo},
            {"warn",     logWarn},
            {"error",    logError},
            {"critical", logCritical},
            {nullptr,    nullptr}
    };
    luaL_newlib(luaState, l);

    return 1;
}
