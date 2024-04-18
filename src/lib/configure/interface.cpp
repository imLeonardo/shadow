#include "configure/interface.h"

#include "configure/configure.h"

namespace shadow {
    namespace config {
        SHADOW_API void init(const char *configFilePath) {
            shadow::Configure::instance().init(configFilePath);
        }

        SHADOW_API void print() {
            shadow::Configure::instance().print();
        }

        SHADOW_API int getInt(const char *key) {
            return shadow::Configure::instance().getInt(key);
        }

        SHADOW_API const char *getString(const char *key) {
            return shadow::Configure::instance().getString(key);
        }
    }
}
