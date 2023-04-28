#ifndef SHADOW_CONFIG_H
#define SHADOW_CONFIG_H

#include "define.h"
#include "singleton.h"
#include "log/log.h"

namespace shadow {
    class Config final : public shadow::Singleton<Config> {
    public:
        explicit Config(Token);

        const char *getLocale();

        bool setLocale(const char *);

        shadow::LogLevel &getLogLevel();

        void setLogLevel(shadow::LogLevel);

        int &getThreadNum();

        void setThreadNum(int);

        void readConfigFile(const char *);

        void print();

    private:
        const char *locale { "en_US.UTF-8" };
        shadow::LogLevel logLevel { shadow::LogLevel::INFO };
        int threadNum { WORK_THREAD_NUM };
    };
} // namespace shadow

#endif // !SHADOW_CONFIG_H