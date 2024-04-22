#ifndef SHADOW_LOGGER_H
#define SHADOW_LOGGER_H

#include <cstdio>
#include <cstdarg>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

#include "define.h"
#include "singleton/singleton.h"
#include "spdlog/spdlog.h"

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

    class Logger final: public shadow::Singleton<Logger> {
    private:
        int mQsize;
        int mThreadNum;
        int mBacktraceNum;
        const char *mPattern;
        std::shared_ptr<spdlog::logger> mLoggerAll;
        std::shared_ptr<spdlog::logger> mLoggerDailyErr;

        void createLoggerAll(shadow::LogLevel);

        void createLoggerError();

    public:
        Logger() = delete;

        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;

        explicit Logger(Singleton<Logger>::Token);

        ~Logger() noexcept override = default;

        ErrCode init(shadow::LogLevel level = shadow::LogLevel::TRACE);

        ErrCode setLogLevel(shadow::LogLevel);

        ErrCode release();

        template<class... Args>
        void trace(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->trace(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log trace failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void debug(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->debug(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log debug failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void info(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->info(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log info failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void warn(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->warn(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log warn failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void error(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->error(fmt, std::forward<Args>(args)...);
                mLoggerDailyErr->error(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log Error failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void critical(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->critical(fmt, std::forward<Args>(args)...);
                mLoggerDailyErr->critical(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log Critical failed:" << ex.what() << std::endl;
            }
        }
    };
} // namespace shadow

#endif // !SHADOW_LOGGER_H
