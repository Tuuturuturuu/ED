// Link y el vuelo en paravela
// ---------------------------
// Estructuras de datos


/*
  En este ejercicio solamente pueden utilizarse las colecciones vistas durante
  esta semana: pilas, colas, o dobles colas.

  En lugar de utilizar las implementaciones vistas en clase, utilizad las que
  vienen implementadas en la biblioteca estándar de C++, que son las
  siguientes:

  - queue, definida en el fichero de cabecera <queue>
    Documentación: https://en.cppreference.com/w/cpp/container/queue

  - stack, definida en el fichero de cabecera <stack>
    Documentación: https://en.cppreference.com/w/cpp/container/stack

  - deque, definida en el fichero de cabecera <deque>
    Documentación: https://en.cppreference.com/w/cpp/container/deque

  Añade los #include con los ficheros de cabecera del TAD o los TADs que
  vais a utilizar.
*/


#include <iostream>
#include <cassert>
#include <fstream>
#include <stack>
#include <queue>
#include <string> 


using namespace std;

// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de entrada (-1). Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
    int num = 0;
    queue<int> cola;
    cin >> num;
    if (num != -1) {
        //lectura de la entrada
        //cola.push(num);
        while (num != -1) {
            cola.push(num);
            cin >> num;
        }

        //resolucion del ej
        stack<int> pila;
        while (!cola.empty()) {
            int n = cola.front();

            if (pila.empty()) {//si la pila esta vacia
                pila.push(n);
                cout << "NO HAY\n";
            }
            else if (pila.top() <= n) {
                while (!pila.empty() && pila.top() <= n) {
                    pila.pop();
                }
                if (pila.empty()) {
                    cout << "NO HAY\n";
                }
                else {
                    cout << pila.top() << "\n";
                }
                pila.push(n);
            }
            else {//si el elemento de la cima de la pila es mayor que n

                cout << pila.top() << "\n";
                pila.push(n);
            }

            //eliminamos el elemento procesado de la cola
            cola.pop();
        }
        cout << "---\n";
        return true;
    }
    else {
        return false;
    }
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Ejecutamos tratar_caso() hasta que nos devuelva `false`
    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
