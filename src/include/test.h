#ifndef TEST_H
#define TEST_H

#include "singleton/singleton.h"
#include "log/log_interface.h"
#include "util/util.h"

class A : public shadow::Singleton<A> {
public:
    explicit A(Token);

    A(const A &a);

    A operator=(const A &a);

    ~A();

    void print();

    A copy(const A &a);

    template<class T>
    T add(T n);

private:
    int a;
};

template<class T>
T A::add(T n) {
    this->a += n;

    return this->a;
}

#endif // !TEST_H
