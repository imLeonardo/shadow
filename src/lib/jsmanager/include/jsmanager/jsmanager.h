#ifndef SHADOW_JSMANAGER_H
#define SHADOW_JSMANAGER_H

#include <cstdio>
#include <cstdarg>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <map>
#include <unordered_map>

#include "define.h"
#include "singleton/singleton.h"

#include "quickjs.h"

namespace shadow {
    namespace js {
        class Context final {
        private:
            uint64_t mID;
            JSRuntime *ptrJsRuntime = nullptr;
            JSContext *ptrJsContext = nullptr;

            std::string LoadFile(std::string);

        public:
            Context() = default;

            explicit Context(uint64_t);

            ~Context() noexcept;

            JSContext *GetContext();

            JSValue EvalFile(const std::string, unsigned evalFlag = 0);
        };

        typedef std::unordered_map<uint64_t, shadow::js::Context> JSContextPool;

        class Manager final: public shadow::Singleton<Manager> {
        private:
            std::atomic<uint64_t> mNowID{0};
            JSContextPool jsContextPoolMap;
        public:
            Manager() = delete;

            explicit Manager(Singleton<Manager>::Token);

            Manager(const Manager &) = delete;

            Manager &operator=(const Manager &) = delete;

            ~Manager() noexcept override = default;

            shadow::js::Context CreateContext();

            ErrCode DelContext(uint64_t);

            shadow::js::Context GetContext(uint64_t);
        };
    } // namespace js
} // namespace shadow

#endif // !SHADOW_JSMANAGER_H
