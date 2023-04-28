//------------------------------------------------------------------------------
/*
  https://github.com/vinniefalco/LuaBridge

  Copyright 2019, Dmitry Tarakanov
  Copyright 2012, Vinnie Falco <vinnie.falco@gmail.com>
  Copyright 2007, Nathan Reed

  License: The MIT License (http://www.opensource.org/licenses/mit-license.php)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
//==============================================================================

#ifndef LUABRIDGE_LUABRIDGE_H
#define LUABRIDGE_LUABRIDGE_H

// All #include dependencies are listed here
// instead of in the individual header files.
//

#define LUABRIDGE_MAJOR_VERSION 2
#define LUABRIDGE_MINOR_VERSION 3
#define LUABRIDGE_VERSION 203

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#include <luabridge/detail/LuaHelpers.h>
#include <luabridge/detail/TypeTraits.h>
#include <luabridge/detail/TypeList.h>
#include <luabridge/detail/FuncTraits.h>
#include <luabridge/detail/Constructor.h>
#include <luabridge/detail/ClassInfo.h>
#include <luabridge/detail/LuaException.h>
#include <luabridge/detail/LuaRef.h>
#include <luabridge/detail/Iterator.h>
#include <luabridge/detail/Userdata.h>
#include <luabridge/detail/CFunctions.h>
#include <luabridge/detail/Security.h>
#include <luabridge/detail/Stack.h>
#include <luabridge/detail/Namespace.h>

#include "log/log.h"

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define DLL_API __declspec(dllexport)
#      else
#        define DLL_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define DLL_API
#   endif // !WIN32
# else
#    define DLL_API
# endif // !SHARED_LIB

#ifndef LUA_VERSION_NUM
#error "Lua headers must be included prior to LuaBridge ones"
#endif

namespace luabridge {
    class DLL_API LuaObj {
    public:
        LuaObj();

        ~LuaObj();

        bool loadFile(const char *);

        luabridge::LuaRef doString(const char *);

        template<class T, class... Args>
        T callFunc(const char *fn, Args &&... args) {
            if(fn == nullptr) {
                throw std::runtime_error("callFunc error:function name is nullptr");
            }
            LuaRef func = LuaRef::getglobal(this->luaState, fn);
            T ret = func(std::forward<Args>(args)...);
            return ret;
        }

    private:
        lua_State *luaState;
        int topIndex;
    };
} // namespace luabridge

int logTrace(lua_State *);

int logDebug(lua_State *);

int logInfo(lua_State *);

int logWarn(lua_State *);

int logError(lua_State *);

int logCritical(lua_State *);

LUAMOD_API "C" {
int luaopen_luabridge_clog(lua_State *);
};

#endif // !LUABRIDGE_LUABRIDGE_H
