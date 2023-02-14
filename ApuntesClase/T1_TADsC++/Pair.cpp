
#include "Pair.h"

using namespace std;

Pair::Pair(A a, B b){
    _a = a;
    _b = b;
}

A Pair::first() const { 
    return _a; }

B Pair::second() const { 
    return _b; }