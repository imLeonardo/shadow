#include "log/interface.h"

#include "log/logger.h"

namespace shadow {
    namespace log {
        SHADOW_API ErrCode Init(int logLevel) {
            return shadow::Logger::Instance().init((shadow::LogLevel)logLevel);
        }

        SHADOW_API ErrCode SetLogLevel(int logLevel) {
            return shadow::Logger::Instance().setLogLevel((shadow::LogLevel)logLevel);
        }

        SHADOW_API ErrCode Release() {
            return shadow::Logger::Instance().Instance();
        }
    }
}