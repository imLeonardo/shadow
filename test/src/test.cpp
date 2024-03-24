#include "test.h"

#include <cstdio>

namespace test {
    ClassA::ClassA() : a(0) {
        printf("create ClassA\n");
    }

    ClassA::ClassA(const ClassA &refClassA) {
        printf("copy ClassA\n");
        this->a = refClassA.a;
    }

    ClassA &ClassA::operator=(const ClassA &refClassA) {
        printf("copy= ClassA\n");
        this->a = refClassA.a;
        return *this;
    }

    ClassA::~ClassA() {
        printf("delete ClassA\n");
    }

    void ClassA::print() const {
        printf("ClassA print %d\n", this->a);
    }
}
