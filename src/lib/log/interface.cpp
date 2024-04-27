#include "log/interface.h"

#include "log/logger.h"

namespace shadow {
    namespace log {
        SHADOW_API ErrCode Init(uint32_t logLevel) {
            return shadow::Logger::Instance().Init(static_cast<shadow::LogLevel>(logLevel));
        }

        SHADOW_API ErrCode SetLogLevel(uint32_t logLevel) {
            return shadow::Logger::Instance().SetLogLevel(static_cast<shadow::LogLevel>(logLevel));
        }

        SHADOW_API ErrCode Release() {
            return shadow::Logger::Instance().Release();
        }
    }
}