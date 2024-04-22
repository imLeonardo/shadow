#include "jsmanager/interface.h"

namespace shadow {
    namespace js {
        SHADOW_API shadow::js::Context CreateContext() {
            return shadow::js::Manager::Instance().CreateContext();
        }
    }
}

