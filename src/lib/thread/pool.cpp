#include "thread/pool.h"

#include "define.h"

namespace shadow {
    namespace thread {
        // the constructor just launches some amount of workers
        Pool::Pool(Token) : isRunning(true) {
            shadow::Log::info("construct thread pool");
        }

        void Pool::createThread(thread_num_t num) {
            thread_num_t i;
            for(i = 0; i < num; ++i)
                workers.emplace_back([&](thread_num_t n) {
                    shadow::Log::info("pool create thread{}", n);
                    while(true) {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(this->queueMutex);
                            this->condition.wait(lock, [this] { return !this->isRunning || !this->tasks.empty(); });
                            if(!this->isRunning && this->tasks.empty())
                                break;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }
                        shadow::Log::info("thread{} call task", n);
                        task();
                    }
                    shadow::Log::info("thread{} exit", n);
                }, i);
        }

        void Pool::joinAll() {
            for(std::thread &worker: workers)
                if(worker.joinable())
                    worker.join();
        }

        void Pool::release() {
            shadow::Log::info("thread pool release");
            this->isRunning = false;
            condition.notify_all();
        }
    }
} // namespace shadow
