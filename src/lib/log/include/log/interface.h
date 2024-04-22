#ifndef SHADOW_LOG_INTERFACE_H
#define SHADOW_LOG_INTERFACE_H

#include "define.h"
#include "log/logger.h"

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define SHADOW_API __declspec(dllexport)
#      else
#        define SHADOW_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define SHADOW_API
#   endif // !WIN32
# else
#    define SHADOW_API
# endif // !SHARED_LIB

namespace shadow {
    namespace log {
        SHADOW_API ErrCode Init(int x = 1);

        SHADOW_API ErrCode setLogLevel(int);

        SHADOW_API ErrCode release();

        template<class... Args>
        SHADOW_API void trace(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().trace(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void debug(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().debug(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void info(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().info(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void warn(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().warn(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void Error(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().error(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void Critical(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().critical(fmt, std::forward<Args>(args)...);
        }
    }
}

#endif // SHADOW_LOG_INTERFACE_H
