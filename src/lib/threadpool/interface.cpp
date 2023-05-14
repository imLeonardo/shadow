#include "threadpool/interface.h"

#include "threadpool/pool.h"

namespace shadow {
    namespace threadpool {
        void createThread(thread_num_t num) {
            shadow::threadpool::Pool::instance().createThread(num);
        }

        void joinAll() {
            shadow::threadpool::Pool::instance().joinAll();
        }

        void release() {
            shadow::threadpool::Pool::instance().release();
        }
    }
}
