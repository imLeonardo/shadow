#ifndef SHADOW_SINGLETON_H
#define SHADOW_SINGLETON_H

#include <iostream>

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define DLL_API __declspec(dllexport)
#      else
#        define DLL_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define DLL_API
#   endif // !WIN32
# else
#    define DLL_API
# endif // !SHARED_LIB

namespace shadow {
    // 单例基类
    template<class T>
    class DLL_API Singleton {
    public:
        Singleton(const Singleton &) = delete;

        Singleton &operator=(const Singleton &) = delete;

        virtual ~Singleton() noexcept = default;

        static T &instance() noexcept(std::is_nothrow_constructible<T>::value) {
            static T instance { Token() };
            return instance;
        }

    protected:
        Singleton() noexcept = default;

        struct Token {};
    };
}

#endif // !SHADOW_SINGLETON_H
