#include "configure/interface.h"

#include "configure/configure.h"

namespace shadow {
    namespace config {
        SHADOW_API void init(const char *configFilePath) {
            shadow::Configure::Instance().init(configFilePath);
        }

        SHADOW_API void print() {
            shadow::Configure::Instance().print();
        }

        SHADOW_API int getInt(const char *key) {
            return shadow::Configure::Instance().getInt(key);
        }

        SHADOW_API const char *getString(const char *key) {
            return shadow::Configure::Instance().getString(key);
        }
    }
}
