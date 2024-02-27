/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no se tendr� en cuenta para la correcci�n.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */


  //@ <answer>
  /*
    Indica el nombre y apellidos de los componentes del grupo
    ---------------------------------------------------------
    Componente 1: Sofia Postigo
    Componente 2: Sergio Tarancon
  */
  //@ </answer>

  /*
    En este ejercicio solamente pueden utilizarse las colecciones vistas durante
    esta semana: pilas, colas, o dobles colas.

    En lugar de utilizar las implemtaciones vistas en clase, utilizad las que
    vienen implementadas en la biblioteca est�ndar de C++, que son las
    siguientes:

    - queue, definida en el fichero de cabecera <queue>
      Documentaci�n: https://en.cppreference.com/w/cpp/container/queue

    - stack, definida en el fichero de cabecera <stack>
      Documentaci�n: https://en.cppreference.com/w/cpp/container/stack

    - deque, definida en el fichero de cabecera <deque>
      Documentaci�n: https://en.cppreference.com/w/cpp/container/deque

    A�ade los #include con los ficheros de cabecera del TAD o los TADs que
    vais a utilizar, aunque est�n fuera de las etiquetas <answer>...</answer>.
  */


#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include <utility>
#include <queue>
#include <deque>

using namespace std;
//@ <answer>
// ----------------------------------------------
// Modificar a partir de aqu�
// ----------------------------------------------
// 
// A�ade los tipos de datos auxiliares y funciones que necesites

//O(t) siendo t = N*T
int  alumnosPendientes(int N, int T, queue<char> examinadores, queue<char> resultados, queue<int> nSuspensos) {
    int i = 0;
    int j;
    
    while (i < T) {
        j = 0;
        while (j < N && !resultados.empty()) {
            switch (examinadores.front()) {
            case 'A':
                //actualizamos la cola de resultados segun el criterio de Agapita
                if (resultados.front() == 'M') {
                    resultados.push(resultados.front()); 
                    nSuspensos.push(nSuspensos.front() + 1);
                }
                break;
            case 'B':
                //actualizamos la cola de resultados segun el criterio de Benito
                if (resultados.front() == 'M') {
                    if (nSuspensos.front() < 2) {
                        resultados.push(resultados.front());
                        nSuspensos.push(nSuspensos.front() + 1);
                    }
                }
                break;
            default:
                //actualizamos la cola de resultados segun el criterio del "guapito"
                resultados.push(resultados.front());
                nSuspensos.push(nSuspensos.front() + 1);
                break;
            }
            nSuspensos.pop();
            resultados.pop();

            //actualizamos la cola de examinadores
            examinadores.push(examinadores.front());
            examinadores.pop();
           
            j++;
        }
        i++;
    }
    return resultados.size();
}


// Implementa aqu� la funci�n para tratar UN caso de prueba. La funci�n
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la funci�n.

//O(t) siendo t = N + M + (N*T)
bool tratar_caso() {

    int N, M, T;
    char elemE, elemR;
    if (cin >> N >> M >> T) {
        queue<char> examinadores;
        queue<char> resultados;
        queue <int> nSuspensos;
        //O(N)
        for (int i = 0; i < N; i++) {
            cin >> elemE;
            examinadores.push(elemE);
        }
        //O(M)
        for (int i = 0; i < M; i++) {
            cin >> elemR;
            resultados.push(elemR);
            nSuspensos.push(0);
        }
        //O(N*T)
        cout << alumnosPendientes(N, T, examinadores, resultados, nSuspensos) << endl;
        return true;
    }
    else return false;
}


// ----------------------------------------------
// No modificar a partir de la l�nea
// ----------------------------------------------
//@ </answer>


int main() {
    // Si est�s ejecutando el programa en tu ordenador, las siguientes l�neas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // �til para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las l�neas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Ejecutamos tratar_caso() hasta que nos devuelva `false`
    while (tratar_caso()) {}

    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}