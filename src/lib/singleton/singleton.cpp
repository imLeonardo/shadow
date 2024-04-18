#include "singleton/singleton.h"

namespace shadow {
    template<class T>
    T &Singleton<T>::instance() noexcept(std::is_nothrow_constructible<T>::value) {
        static T instance{Token()};
        return instance;
    }
}