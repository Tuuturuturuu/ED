#ifndef PAIR_H
#define PAIR_H

#include<iostream>
using namespace std;

template <class A, class B>

class Pair{

    private:
        A _a;
        B _b;

    public:
        Pair(A a, B b);
        A first() const;
        B second() const;
}

#endif