#include "log/logger.h"

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/async_logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"

namespace shadow {
    Logger::Logger(Singleton<Logger>::Token) {

    }

    ErrCode Logger::init(shadow::LogLevel level) {
        try {
            // 设置线程
            spdlog::init_thread_pool(1024, 1);
            // 输出
            auto sinkStdout = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto sinkDailyAll = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/main.log", 0, 0);
            spdlog::sinks_init_list sinks { sinkStdout, sinkDailyAll };
            const char *pattern = "%^[%Y-%m-%d %H:%M:%S.%e][%t][%l] %v%$";
            mLoggerAll = std::make_shared<spdlog::async_logger>("mLoggerAll", sinks, spdlog::thread_pool());
            mLoggerAll->set_level((spdlog::level::level_enum)level);
            mLoggerAll->set_pattern(pattern);
            mLoggerAll->enable_backtrace(32);
            spdlog::register_logger(mLoggerAll);

            // 错误日志文件
            mLoggerDailyErr = spdlog::daily_logger_mt("mLoggerDailyErr", "logs/error.log", 2, 0);
            mLoggerDailyErr->set_level(spdlog::level::err);
            mLoggerDailyErr->set_pattern(pattern);
            mLoggerDailyErr->enable_backtrace(32);
            spdlog::register_logger(mLoggerDailyErr);

            return ErrCode::SUCCESS;
        } catch(const spdlog::spdlog_ex &ex) {
            std::cout << "log init failed:" << ex.what() << std::endl;

            return ErrCode::FAIL;
        }
    }

    ErrCode Logger::setLogLevel(shadow::LogLevel logLevel) {
        mLoggerAll->set_level((spdlog::level::level_enum)logLevel);
        //
        return ErrCode::SUCCESS;
    }

    ErrCode Logger::release() {
        try {
            spdlog::drop_all();
            spdlog::shutdown();
            //
            return ErrCode::SUCCESS;
        } catch(const spdlog::spdlog_ex &ex) {
            std::cout << "log release failed:" << ex.what() << std::endl;
            //
            return ErrCode::FAIL;
        }
    }
} // namespace shadow
