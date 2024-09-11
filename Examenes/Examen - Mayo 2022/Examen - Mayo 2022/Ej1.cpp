//#include <iostream>
//#include <fstream>
//#include<stack>
//#include <list>
//#include <cassert>
//
//using namespace std;
//
//void reconstruir(list<int>& lista) {
//    if (!lista.empty()) {
//        stack<int> pila;
//        auto it = lista.begin();
//        bool end = false;
//        while (!end && *it <= 0) {
//            lista.pop_front();
//            it = lista.begin();
//            if (lista.empty()) { end = true; }
//        }
//        if (!lista.empty()) {
//            pila.push(*it);//metemos en la pila el primer elemento positivo
//
//            while (it != lista.end()) {
//                if (*it > 0) {
//                    pila.push(*it);
//                }
//                else {
//                    if ((-1 * pila.top()) != *it) {
//                        *it = (-1 * pila.top());
//                    }
//                    pila.pop();
//                }
//                ++it;
//            }
//
//            while (!pila.empty()) {
//                lista.push_back(pila.top() * -1);
//                pila.pop();
//            }
//            lista.pop_back();
//        }
//    }
//}
//
//
//// Función que trata un caso de prueba
//bool tratar_caso() {
//    list<int>  lista;
//    bool ret = true;
//    int N, num;
//    if (cin >> N) {
//        for (int i = 0; i < N; i++) {
//            cin >> num;
//            lista.push_back(num);
//        }
//
//        reconstruir(lista);
//        for (auto it = lista.begin(); it != lista.end(); ++it) {
//            cout << *it << " ";
//        }
//        cout << "\n";
//    }
//    else {
//        ret = false;
//    }
//    return ret;
//}
//
//
//int main() {
//#ifndef DOMJUDGE
//    std::ifstream in("sample.in");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf());
//#endif
//    // La entrada comienza por el número de casos de prueba
//   
//
//    // Ejecutamos tratar_caso() tantas veces como el primer número leído
//    while (tratar_caso()) {
//       
//    }
//
//#ifndef DOMJUDGE
//    std::cin.rdbuf(cinbuf);
//#endif
//
//    return 0;
//}