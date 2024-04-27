#include <memory>

#include "configure/configure.h"

#include "log/interface.h"
#include "util/util.h"

namespace shadow {
    Configure::Configure(Singleton<Configure>::Token) {

    }

    void Configure::Init(const char *configFilePath) {
        if(configFilePath == nullptr) {
            throw std::runtime_error("Configure file is null");
        }
    }

    void Configure::Print() {

    }

    int64_t Configure::GetInt(const char *key) {
        return 0;
    }

    const char *Configure::GetString(const char *key) {
        return "";
    }
} // namespace shadow
