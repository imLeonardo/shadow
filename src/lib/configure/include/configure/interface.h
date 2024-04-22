#ifndef SHADOW_CONFIGURE_INTERFACE_H
#define SHADOW_CONFIGURE_INTERFACE_H

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

namespace shadow {
    namespace config {
        SHADOW_API void Init(const char *);

        SHADOW_API void Print();

        SHADOW_API int GetInt(const char *);

        SHADOW_API const char* GetString(const char *);
    }
}

#endif //SHADOW_CONFIGURE_INTERFACE_H
