#include "configure/interface.h"

#include "configure/configure.h"

namespace shadow {
    namespace config {
        SHADOW_API void Init(const char *configFilePath) {
            shadow::Configure::Instance().init(configFilePath);
        }

        SHADOW_API void Print() {
            shadow::Configure::Instance().print();
        }

        SHADOW_API int GetInt(const char *key) {
            return shadow::Configure::Instance().getInt(key);
        }

        SHADOW_API const char *GetString(const char *key) {
            return shadow::Configure::Instance().getString(key);
        }
    }
}
