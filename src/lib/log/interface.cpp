#include "log/interface.h"

#include "log/logger.h"

namespace shadow {
    namespace log {
        SHADOW_API ErrCode init(int logLevel) {
            return shadow::Logger::instance().init((shadow::LogLevel)logLevel);
        }

        SHADOW_API ErrCode setLogLevel(int logLevel) {
            return shadow::Logger::instance().setLogLevel((shadow::LogLevel)logLevel);
        }

        SHADOW_API ErrCode release() {
            return shadow::Logger::instance().release();
        }
    }
}