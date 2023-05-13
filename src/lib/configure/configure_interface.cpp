#include "configure/configure_interface.h"

#include "configure/configure.h"

namespace shadow {
    namespace config {
        SHADOW_API void init(const char *configFilePath) {
            shadow::Configure::instance().init(configFilePath);
        }

        SHADOW_API void print() {
            shadow::Configure::instance().print();
        }

        SHADOW_API int getint(const char *key) {
            return shadow::Configure::instance().getint(key);
        }

        SHADOW_API const char *getstring(const char *key) {
            return shadow::Configure::instance().getstring(key);
        }
    }
}
