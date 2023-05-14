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
        SHADOW_API void init(const char *);

        SHADOW_API void print();

        SHADOW_API int getInt(const char *);

        SHADOW_API const char* getString(const char *);
    }
}

#endif //SHADOW_CONFIGURE_INTERFACE_H
