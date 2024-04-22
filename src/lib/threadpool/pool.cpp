#include "threadpool/pool.h"

#include "define.h"

namespace shadow {
    namespace threadpool {
        // the constructor just launches some amount of workers
        Pool::Pool(Singleton<Pool>::Token) : mIsRunning(true) {
            shadow::log::info("construct threadpool");
        }

        void Pool::createThread(thread_num_t num) {
            thread_num_t i;
            for(i = 0; i < num; ++i)
                this->mWorkers.emplace_back([&](thread_num_t n) {
                    shadow::log::info("pool create thread{}", n);
                    while(true) {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(this->mQueueMutex);
                            this->mCondition.wait(lock, [this] { return !this->mIsRunning || !this->mTasks.empty(); });
                            if(!this->mIsRunning && this->mTasks.empty())
                                break;
                            task = std::move(this->mTasks.front());
                            this->mTasks.pop();
                        }
                        shadow::log::info("thread{} call task", n);
                        task();
                    }
                    shadow::log::info("thread{} Exit", n);
                }, i);
        }

        void Pool::joinAll() {
            for(std::thread &worker: this->mWorkers)
                if(worker.joinable())
                    worker.join();
        }

        void Pool::release() {
            shadow::log::info("threadpool Release");
            this->mIsRunning = false;
            this->mCondition.notify_all();
        }
    }
} // namespace shadow
