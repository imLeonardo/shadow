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
        SHADOW_API ErrCode init(int x = 1);

        SHADOW_API ErrCode setLogLevel(int);

        SHADOW_API ErrCode release();

        template<class... Args>
        SHADOW_API void trace(const char *fmt, Args &&... args) {
            shadow::Logger::instance().trace(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void debug(const char *fmt, Args &&... args) {
            shadow::Logger::instance().debug(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void info(const char *fmt, Args &&... args) {
            shadow::Logger::instance().info(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void warn(const char *fmt, Args &&... args) {
            shadow::Logger::instance().warn(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void error(const char *fmt, Args &&... args) {
            shadow::Logger::instance().error(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void critical(const char *fmt, Args &&... args) {
            shadow::Logger::instance().critical(fmt, std::forward<Args>(args)...);
        }
    }
}

#endif // SHADOW_LOG_INTERFACE_H
