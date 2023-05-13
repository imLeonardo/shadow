#include "test.h"

A::A(Token) : a(0) {
    shadow::log::debug("create A");
}

A::A(const A &a) {
    shadow::log::debug("copy1 A");
    this->copy(a);
}

A A::operator=(const A &a) {
    shadow::log::debug("copy2 A");
    return this->copy(a);
}

A::~A() {
    shadow::log::debug("delete A");
}

void A::print() {
    shadow::log::info("A print {}", this->a);
}

A A::copy(const A &a) {
    return a;
}
