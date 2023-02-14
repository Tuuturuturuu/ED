
#include<iostream>
#include<string>
#include <set>
#include "Pair.h"
using namespace std;

int main(){
    Pair<int, string> p(4, ” hola”);

    cout << p.first() << ” ” << p.second() << ”\n”;
    //----------------------------------------------
    set <string> s;
    s.insert("hola");
    s.insert("adios");

    cout << s.size() << endl; //imprime 2
    cout << s.count("hola") << endl; //imprime 1
    cout << s.count("HOLA") << endl; //imprime 0

    s.erase("adios");
    cout << s.size() << endl; // imprime 1
    s.clear();
    cout << s.size() << endl; // imprime 0

    return 0;
}