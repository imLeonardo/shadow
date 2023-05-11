#ifndef SHADOW_LOG_H
#define SHADOW_LOG_H

#include <cstdio>
#include <cstdarg>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

#include "define.h"
#include "singleton.h"
#include "spdlog/spdlog.h"

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define DLL_API __declspec(dllexport)
#      else
#        define DLL_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define DLL_API
#   endif // !WIN32
# else
#    define DLL_API
# endif // !SHARED_LIB

namespace shadow {
    enum class LogLevel {
        TRACE = spdlog::level::level_enum::trace,
        DEBUG = spdlog::level::level_enum::debug,
        INFO = spdlog::level::level_enum::info,
        WARN = spdlog::level::level_enum::warn,
        ERR = spdlog::level::level_enum::err,
        CRITICAL = spdlog::level::level_enum::critical,
        OFF = spdlog::level::level_enum::off
    };

    class DLL_API Log final {
    private:
        static std::shared_ptr<spdlog::logger> loggerAll;
        static std::shared_ptr<spdlog::logger> loggerDailyErr;

    public:
        Log() = delete;

        Log(const Log &) = delete;

        Log &operator=(const Log &) = delete;

        ~Log() noexcept = default;

        static ErrCode init(shadow::LogLevel level = shadow::LogLevel::TRACE);

        static ErrCode setLogLevel(shadow::LogLevel);

        static ErrCode release();

        template<class... Args>
        static void trace(const char *fmt, Args &&... args) {
            try {
                loggerAll->trace(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log trace failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        static void debug(const char *fmt, Args &&... args) {
            try {
                loggerAll->debug(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log debug failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        static void info(const char *fmt, Args &&... args) {
            try {
                loggerAll->info(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log info failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        static void warn(const char *fmt, Args &&... args) {
            try {
                loggerAll->warn(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log warn failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        static void error(const char *fmt, Args &&... args) {
            try {
                loggerAll->error(fmt, std::forward<Args>(args)...);
                loggerDailyErr->error(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log error failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        static void critical(const char *fmt, Args &&... args) {
            try {
                loggerAll->critical(fmt, std::forward<Args>(args)...);
                loggerDailyErr->critical(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log critical failed:" << ex.what() << std::endl;
            }
        }
    };
} // namespace shadow

#endif // !SHADOW_LOG_H
