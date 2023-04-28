#include "test.h"

A::A(Token) : a(0) {
    shadow::Log::debug("create A");
}

A::A(const A &a) {
    shadow::Log::debug("copy1 A");
    this->copy(a);
}

A A::operator=(const A &a) {
    shadow::Log::debug("copy2 A");
    return this->copy(a);
}

A::~A() {
    shadow::Log::debug("delete A");
}

void A::print() {
    shadow::Log::info("A print {}", this->a);
}

A A::copy(const A &a) {
    return a;
}
