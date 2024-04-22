#include "threadpool/interface.h"

#include "threadpool/pool.h"

namespace shadow {
    namespace threadpool {
        void CreateThread(ThreadNum_t num) {
            shadow::threadpool::Pool::Instance().CreateThread(num);
        }

        void JoinAll() {
            shadow::threadpool::Pool::Instance().JoinAll();
        }

        void Release() {
            shadow::threadpool::Pool::Instance().Release();
        }
    }
}
