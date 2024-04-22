#include "configure/interface.h"

#include "configure/configure.h"

namespace shadow {
    namespace config {
        SHADOW_API void Init(const char *configFilePath) {
            shadow::Configure::Instance().Init(configFilePath);
        }

        SHADOW_API void Print() {
            shadow::Configure::Instance().Print();
        }

        SHADOW_API int GetInt(const char *key) {
            return shadow::Configure::Instance().GetInt(key);
        }

        SHADOW_API const char *GetString(const char *key) {
            return shadow::Configure::Instance().GetString(key);
        }
    }
}
