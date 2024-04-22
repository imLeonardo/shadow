#include "log/interface.h"

#include "log/logger.h"

namespace shadow {
    namespace log {
        SHADOW_API ErrCode Init(int logLevel) {
            return shadow::Logger::Instance().Init((shadow::LogLevel) logLevel);
        }

        SHADOW_API ErrCode SetLogLevel(int logLevel) {
            return shadow::Logger::Instance().SetLogLevel((shadow::LogLevel) logLevel);
        }

        SHADOW_API ErrCode Release() {
            return shadow::Logger::Instance().Instance();
        }
    }
}