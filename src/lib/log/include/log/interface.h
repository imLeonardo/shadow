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

        SHADOW_API ErrCode SetLogLevel(int);

        SHADOW_API ErrCode Release();

        template<class... Args>
        SHADOW_API void Trace(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().Trace(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void Debug(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().Debug(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void Info(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().Info(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void Warn(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().Warn(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void Error(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().Error(fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        SHADOW_API void Critical(const char *fmt, Args &&... args) {
            shadow::Logger::Instance().Critical(fmt, std::forward<Args>(args)...);
        }
    }
}

#endif // SHADOW_LOG_INTERFACE_H
