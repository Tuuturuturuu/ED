// Nombre del alumno Sofia Postigo
// Usuario del Juez E52


#include <iostream>
#include <iomanip>
#include <fstream>
#include<string>
#include "Stack.h"

using namespace std;

bool isBalanced(string s) {
    Stack<char> stack;
    bool stop = false;
    int i = 0;
    char c;
    while ( i < s.size()) {

        c = s[i];
        switch (c) {
        case '(': case '[': case '{':
            stack.push(c);
            break;
        case ')': 
            if (stack.empty() || stack.top() != '(') 
                return false;
            stack.pop();
            break;
        case '}':
            if (stack.empty() || stack.top() != '{')
                return false;
            stack.pop();
            break;
        case ']':
            if (stack.empty() || stack.top() != '[')
                return false;
            stack.pop();
            break;
        }
        i++;
    }
    if (stack.empty())
        return true;
    else
        return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string s;
    getline(cin, s);

    if (!std::cin)
        return false;

    //escribir sol
    if (isBalanced(s))
        cout << "SI" << endl;
    else
        cout << "NO" << endl;

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}