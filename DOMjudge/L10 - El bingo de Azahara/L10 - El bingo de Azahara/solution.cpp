
/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1:Sergio Tarancon
   Componente 2:Sofia Postigo
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <queue>
#include <utility>
#include <vector>
#include <set>
//Añade los include que necesites

using namespace std;

//mapa cuyas claves son los numeros que canta Azahara y cuyos valores son listas que contienen los nombres 
//de los jugadores los cuales tienen ese numero (clave) en su carton
using mapaBingos = unordered_map<int, vector<string>>;

//mapa cuyas claves son los nombres de los jugadores, y cuyos valores son el numero de elementos del carton 
//del jugador
using mapaJugadores = unordered_map<string, int>;

//Complejidad: O((N*M) + (T*N) + N) --> O(N(M+T+1)) --> O(N * Z) siendo Z = M+T+1
// siendo siendo N el numero de jugadores, M el numero de elementos del carton de cada jugador,
// y siendo siendo T el numero de numeros cantados por Azahara hasta que hay algun bingo
bool tratar_caso() {
	bool ret = true;
	int N, num;
	string nombre;
	
	mapaJugadores mapPlayers;
	mapaBingos mapBingos;

	set<string> setGanadores;

	cin >> N;
	if (N == 0) {
		ret = false;
	} 
	else {
		
		for (int i = 0; i < N; i++) {//O(N*M) siendo N el numero de jugadores
			cin >> nombre;
			cin >> num;
			while (num != 0) {//O(M) siendo M el numero de elementos del carton de cada jugador
				mapPlayers[nombre]++;
				mapBingos[num].push_back(nombre);
				cin >> num;
			}
		}

		bool hayBingo = false;
		while (!hayBingo) {//O(T * N) siendo T el numero de numeros cantados por Azahara hasta que se hay algun bingo
			cin >> num;
			if (mapBingos.count(num) > 0) {//ese "num" se encuentra en el carton de algun jugador, pues está en el mapa de Bingos
				
				vector<string> jugadores = mapBingos[num];
				
				for (int i = 0; i < jugadores.size(); i++ ) {//O(N) siendo N el numero de jugadores que tienen en su carta "num" (en el peor de los casos todos los jugadores)
		
					string jugador = jugadores[i];

					mapPlayers[jugador]--;

					if (mapPlayers[jugador] == 0) {
						setGanadores.insert(jugador);
						hayBingo = true;
					}
				}
			}
		}
		//O(N) siendo N el numero de jugadores que consiguen ingo (en el peor caso N, es decir todos los jugadores)
		for (auto it = setGanadores.begin(); it != setGanadores.end(); ++it) {
			cout << *it << " ";
		}
		cout << "\n";
	}

	return ret;
}

int main() {
	// Si estás ejecutando el programa en tu ordenador, las siguientes líneas
	// redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
	// útil para no tener que teclear los casos de prueba por teclado cada vez
	// que ejecutas el programa.
	//
	// Si prefieres teclear los casos de prueba por teclado en tu ordenador,
	// comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (tratar_caso()) {	}

	// Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
