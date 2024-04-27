#include "threadpool/pool.h"

#include "define.h"

namespace shadow {
    namespace threadpool {
        // the constructor just launches some amount of workers
        Pool::Pool(Singleton<Pool>::Token) : mIsRunning(true) {
            shadow::log::Info("construct threadpool");
        }

        void Pool::CreateThread(ThreadNum_t) {
            for(ThreadNum_t i = 0; i < num; ++i)
                this->mWorkers.emplace_back([&](ThreadNum_t n) {
                    shadow::log::Info("pool create thread{}", n);
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
                        shadow::log::Info("thread{} call task", n);
                        task();
                    }
                    shadow::log::Info("thread{} Exit", n);
                }, i);
        }

        void Pool::JoinAll() {
            for(std::thread &worker: this->mWorkers)
                if(worker.joinable())
                    worker.join();
        }

        void Pool::Release() {
            shadow::log::Info("threadpool Release");
            this->mIsRunning = false;
            this->mCondition.notify_all();
        }
    }
} // namespace shadow
