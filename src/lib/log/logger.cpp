#include "log/logger.h"

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/async_logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"

namespace shadow {
    Logger::Logger(Singleton<Logger>::Token):
            mQsize(1024),
            mThreadNum(4),
            mBacktraceNum(32),
            mPattern("%^[%Y-%m-%d %H:%M:%S.%e][%t][%l] %v%$") {

    }

    void Logger::CreateLoggerAll(shadow::LogLevel level) {
        auto sinkStdout = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto sinkDailyAll = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/main.log", 0, 0);
        spdlog::sinks_init_list sinks{sinkStdout, sinkDailyAll};
        this->mLoggerAll = std::make_shared<spdlog::async_logger>("mLoggerAll", sinks, spdlog::thread_pool());
        this->mLoggerAll->set_level(static_cast<spdlog::level::level_enum>(level));
        this->mLoggerAll->set_pattern(this->mPattern);
        this->mLoggerAll->enable_backtrace(this->mBacktraceNum);
        spdlog::register_logger(this->mLoggerAll);
    }

    void Logger::CreateLoggerError() {
        this->mLoggerDailyErr = spdlog::daily_logger_mt("mLoggerDailyErr", "logs/Error.log", 0, 0);
        this->mLoggerDailyErr->set_level(spdlog::level::err);
        this->mLoggerDailyErr->set_pattern(this->mPattern);
        this->mLoggerDailyErr->enable_backtrace(this->mBacktraceNum);
    }

    ErrCode Logger::Init(shadow::LogLevel level) {
        try {
            spdlog::init_thread_pool(this->mQsize, this->mThreadNum);
            this->CreateLoggerAll(level);
            this->CreateLoggerError();

            return ErrCode::SUCCESS;
        } catch(const spdlog::spdlog_ex &ex) {
            std::cout << "log Init failed:" << ex.what() << std::endl;

            return ErrCode::FAIL;
        }
    }

    ErrCode Logger::SetLogLevel(shadow::LogLevel logLevel) {
        this->mLoggerAll->set_level(static_cast<spdlog::level::level_enum>(logLevel));
        //
        return ErrCode::SUCCESS;
    }

    ErrCode Logger::Release() {
        try {
            spdlog::drop_all();
            spdlog::shutdown();
            //
            return ErrCode::SUCCESS;
        } catch(const spdlog::spdlog_ex &ex) {
            std::cout << "log Release failed:" << ex.what() << std::endl;
            //
            return ErrCode::FAIL;
        }
    }
} // namespace shadow
