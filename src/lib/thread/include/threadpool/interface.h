#ifndef SHADOW_THREADPOOL_INTERFACE_H
#define SHADOW_THREADPOOL_INTERFACE_H

#include "threadpool/pool.h"

#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>

#include "define.h"

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define SHADOW_API __declspec(dllexport)
#      else
#        define SHADOW_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define SHADOW_API
#   endif // !WIN32
# else
#    define SHADOW_API
# endif // !SHARED_LIB

namespace shadow {
    namespace threadpool {
        SHADOW_API void CreateThread(ThreadNum_t);

        template<class F, class... Args>
        SHADOW_API auto AddTask(const char *reason, F &&f, Args &&... args)->std::future<typename std::result_of<F(Args...)>::type> {
            return shadow::threadpool::Pool::Instance().AddTask(reason, f, std::forward<Args>(args)...);
        }

        SHADOW_API void JoinAll();

        SHADOW_API void Release();
    }
}

#endif //SHADOW_THREADPOOL_INTERFACE_H
