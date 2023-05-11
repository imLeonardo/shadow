//
// Created by leo on 2022/6/14.
//

#include "luabridge/luabridge.h"

namespace luabridge {
    LuaObj::LuaObj() : luaState(luaL_newstate()), topIndex(0) {
        shadow::Log::init();
        shadow::Log::debug("luaobj");
        luaL_openlibs(this->luaState);
    }

    LuaObj::~LuaObj() {
        shadow::Log::debug("~luaobj");
        shadow::Log::release();
        if(this->luaState != nullptr) {
            lua_close(this->luaState);
            this->luaState = nullptr;
        }
    }

    bool LuaObj::loadFile(const char *filePath) {
        int ret = luaL_dofile(this->luaState, filePath);
        if(ret != LUA_OK) {
            throw std::runtime_error("luaobj load file error,file:"
                                     + std::string(filePath)
                                     + ",error:" + lua_tostring(this->luaState, -1));
        }
        return true;
    }

    luabridge::LuaRef LuaObj::doString(const char *) {
        return LuaRef::fromStack(this->luaState);
    }
} // namespace luabridge

int logTrace(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::Log::trace(s);
    return 1;
}

int logDebug(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::Log::debug(s);
    return 1;
}

int logInfo(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::Log::info(s);
    return 1;
}

int logWarn(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::Log::warn(s);
    return 1;
}

int logError(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::Log::error(s);
    return 1;
}

int logCritical(lua_State *luaState) {
    const char *s = luaL_tolstring(luaState, 1, nullptr);
    shadow::Log::critical(s);
    return 1;
}

int luaopen_luabridge_clog(lua_State *lua_state) {
    const luaL_Reg lib[] = {
            { "trace",    logTrace },
            { "debug",    logDebug },
            { "info",     logInfo },
            { "warn",     logWarn },
            { "error",    logError },
            { "critical", logCritical },
            { nullptr,    nullptr }
    };
    luaL_newlib(lua_state, lib);

    return 1;
}
