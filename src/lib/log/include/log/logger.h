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

        void CreateLoggerAll(shadow::LogLevel level);

        void CreateLoggerError();

    public:
        Logger() = delete;

        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;

        explicit Logger(Singleton<Logger>::Token);

        ~Logger() noexcept override = default;

        ErrCode Init(shadow::LogLevel level = shadow::LogLevel::TRACE);

        ErrCode SetLogLevel(shadow::LogLevel logLevel);

        ErrCode Release();

        template<class... Args>
        void Trace(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->trace(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log Trace failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void Debug(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->debug(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log Debug failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void Info(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->info(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log Info failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void Warn(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->warn(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log Warn failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void Error(const char *fmt, Args &&... args) {
            try {
                mLoggerAll->error(fmt, std::forward<Args>(args)...);
                mLoggerDailyErr->error(fmt, std::forward<Args>(args)...);
            } catch(const spdlog::spdlog_ex &ex) {
                std::cout << "log Error failed:" << ex.what() << std::endl;
            }
        }

        template<class... Args>
        void Critical(const char *fmt, Args &&... args) {
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
