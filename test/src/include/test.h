#ifndef TEST_H
#define TEST_H

namespace test {
    class ClassA {
    public:
        ClassA();

        ClassA(const ClassA &refClassA);

        ClassA &operator=(const ClassA &refClassA);

        ~ClassA();

        void print() const;

        template<class T>
        T add(T n);

    private:
        int a;
    };

    template<class T>
    T ClassA::add(T n) {
        this->a += n;

        return this->a;
    }
}

#endif // !TEST_H
