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

#include "singleton.h"
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

namespace shadow {
    namespace thread {
        class DLL_API Pool final : public shadow::Singleton<Pool> {
        public:
            explicit Pool(Token);

            void createThread(thread_num_t);

            void joinAll();

            void release();

            template<class F, class... Args>
            auto addTask(const char*, F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
        private:
            // need to keep track of threads, so we can join them
            std::vector<std::thread> workers;
            // the task queue
            std::queue<std::function<void()>> tasks;
            // synchronization
            std::mutex queueMutex;
            std::condition_variable condition;
            std::atomic<bool> isRunning;
        };

        // add new task to the queue
        template<class F, class... Args>
        auto Pool::addTask(const char *way, F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
            shadow::Log::info("pool add task,way:{}", way);
            using return_type = typename std::result_of<F(Args...)>::type;

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(queueMutex);

                // don't allow adding task when the pool not running
                if(!isRunning)
                    throw std::runtime_error("add task on pool not running");

                tasks.emplace([task]() { (*task)(); });
            }
            condition.notify_one();

            return res;
        }
    }
} // namespace shadow

#endif // !SHADOW_POOL_H
