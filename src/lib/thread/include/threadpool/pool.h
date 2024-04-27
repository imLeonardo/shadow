#ifndef SHADOW_POOL_H
#define SHADOW_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>

#include "singleton/singleton.h"
#include "log/interface.h"

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
        class SHADOW_API Pool final: public shadow::Singleton<Pool> {
        public:
            explicit Pool(Singleton<Pool>::Token);

            void CreateThread(ThreadNum_t);

            void JoinAll();

            void Release();

            template<class F, class... Args>
            auto addTask(const char *, F &&f, Args &&... args)->std::future<typename std::result_of<F(Args...)>::type>;

        private:
            // need to keep track of threads, so we can join them
            std::vector<std::thread> mWorkers;
            // the task queue
            std::queue<std::function<void()>> mTasks;
            // synchronization
            std::mutex mQueueMutex;
            std::condition_variable mCondition;
            std::atomic<bool> mIsRunning;
        };

        // add new task to the queue
        template<class F, class... Args>
        auto Pool::addTask(const char *reason, F &&f, Args &&... args)->std::future<typename std::result_of<F(Args...)>::type> {
            shadow::log::Info("theadpool add task,reason:{}", reason);
            using return_type = typename std::result_of<F(Args...)>::type;

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(this->mQueueMutex);

                // don't allow adding task when the pool not running
                if(!this->mIsRunning)
                    throw std::runtime_error("add task on pool not running");

                this->mTasks.emplace([task]() {
                    (*task)();
                });
            }
            this->mCondition.notify_one();

            return res;
        }
    }
} // namespace shadow

#endif // !SHADOW_POOL_H
