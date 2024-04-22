#include "threadpool/interface.h"

#include "threadpool/pool.h"

namespace shadow {
    namespace threadpool {
        void createThread(thread_num_t num) {
            shadow::threadpool::Pool::Instance().createThread(num);
        }

        void joinAll() {
            shadow::threadpool::Pool::Instance().joinAll();
        }

        void Release() {
            shadow::threadpool::Pool::Instance().release();
        }
    }
}
