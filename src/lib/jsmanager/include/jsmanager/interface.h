#ifndef SHADOW_JSMANAGER_INTERFACE_H
#define SHADOW_JSMANAGER_INTERFACE_H

#include "define.h"

#include "quickjs.h"

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define SHADOW_API __declspec(dllexport)
#      else
#        define SHADOW_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define SHADOW_API
#   endif // !WIN32
# else
#    define SHADOW_API
# endif // !SHARED_LIB

#include "jsmanager/jsmanager.h"

namespace shadow {
    namespace js {
        SHADOW_API shadow::js::Context CreateContext();
    }
}

#endif // SHADOW_JSMANAGER_INTERFACE_H
