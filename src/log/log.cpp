#include "log/log.h"

#include "spdlog/async.h"
#include "spdlog/async_logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"

namespace shadow {
    ErrCode Log::init(shadow::LogLevel level) {
        try {
            // 设置线程
            spdlog::init_thread_pool(256, 1);
            // 输出
            auto sinkStdout = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto sinkDailyAll = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/main.log", 2, 0);
            spdlog::sinks_init_list sinks { sinkStdout, sinkDailyAll };
            const char *pattern = "%^[%Y-%m-%d %H:%M:%S.%e][%t][%l] %v%$";
            loggerAll = std::make_shared<spdlog::async_logger>("loggerAll", sinks, spdlog::thread_pool());
            loggerAll->set_level((spdlog::level::level_enum)level);
            loggerAll->set_pattern(pattern);
            spdlog::register_logger(loggerAll);

            // 错误日志文件
            loggerDailyErr = spdlog::daily_logger_mt("loggerDailyErr", "logs/error.log", 2, 0);
            loggerDailyErr->set_level(spdlog::level::err);
            loggerDailyErr->set_pattern(pattern);
            spdlog::register_logger(loggerDailyErr);

            return ErrCode::SUCCESS;
        } catch(const spdlog::spdlog_ex &ex) {
            std::cout << "log init failed:" << ex.what() << std::endl;

            return ErrCode::FAIL;
        }
    }

    ErrCode Log::setLogLevel(shadow::LogLevel logLevel) {
//        auto logger_all = spdlog::get("logger_all");
        loggerAll->set_level((spdlog::level::level_enum)logLevel);
        return ErrCode::SUCCESS;
    }

    ErrCode Log::release() {
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
