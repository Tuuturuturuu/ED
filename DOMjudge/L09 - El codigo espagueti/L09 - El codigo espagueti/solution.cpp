/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1:Sergio Tarancon
   Componente 2: Sofia Postigo
 */


 // A�ade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <utility>
#include <map>
#include <string>
using namespace std;

// En este ejercicio utilizamos la clase `map` de la librer�a est�ndar de C++, 
// en lugar de la clase MapTree vista en clase. La interfaz de `map` es casi
// la misma que la de `MapTree`. Consulta el FAQ de la pr�ctica para ver las
// diferencias principales.

// Tambi�n puedes ver la documentaci�n de la clase `map` en:
// https://en.cppreference.com/w/cpp/container/map



// Define un tipo para representar los programas

using programa = map<int, pair<string, string>>;

// Define un tipo para almacenar el valor de cada variable del programa

using memoria = map<string, int>;


// Funci�n para ejecutar un programa.
//
// Recibe:
//    - El programa `p` a ejecutar
//    - M�ximo n�mero de instrucciones a ejecutar. Si se intenta ejecutar un n�mero mayor
//      de instrucciones, se detiene la ejecuci�n y se devuelve la memoria correspondiente
//      al estado del programa en el momento de detenerse.
//
// Devuelve un par con dos componentes:
//    - El estado de la memoria tras la ejecuci�n del programa, bien sea porque se haya
//      ejecutado la �ltima instrucci�n, o bien porque se haya alcanzado el l�mite de
//      instrucciones ejecutadas indicado por el par�metro `max_pasos`.  
//    - Un booleano que indique si se ha producido un error en la ejecuci�n del programa
//      Devuelve `true` si se ha encontrado ejecutar una instrucci�n "GOTO n", donde n
//      es un n�mero de instrucci�n que no se encuentra en el programa. Devuelve `false`
//      en caso contrario. Si el valor de esta componente es `true`, la primera componente
//      del par es irrelevante.

// Indica el coste, en el caso peor, de la funci�n `ejecutar`, en funci�n del tama�o
// del programa `p` y de `num_pasos`

//Complejidad: O(N logM ), siendo N = max_pasos en el peor de los casos, 
// y siendo M el numero de elementos del mapa sobre el que se hacen las operaciones find() y count(), las cuales tienen complejidad logar�tmica
// es decir, en el caso de que se procese una instruccion INCR M ser� el numero de instrucciones del programa, o entradas de "p", y en el caso de que la instruccion 
//sea GOTO M ser� el numero de variables existentes en el mapa de variables
pair<memoria, bool> ejecutar(const programa& p, int max_pasos) {
	int n = 0;
	bool error = false;
	memoria variables;
	//SI TE PASAN UN MAPA CONSTANTE PARA ITERAR SOBRE EL, AUNQ FIND SEA UN METODO CONSTANTE 
	//EL ITERADOR NO LO ES, ASIQ EN LUGAR DE USAR ::ITERATOR USAMOS ::CONST_ITERATOR
	programa::const_iterator itP = p.cbegin();

	while (itP != p.cend() && (n < max_pasos) && !error) {
		bool GOTOok = false;
		int k = itP->first;
		pair<string, string> v = itP->second;
		//k = numero de linea
		//v = pair<instruccion, variable>
		//v.first = instruccion
		//v.second = variable
		
		if (v.first == "INCR") {
			//tambien se podr�a hacer con un iterador sobre "variables" y el metodo find():
			//memoria::iterator itM = variables.find(v.second);
			//if(itM != variables.end()){//nlogn
			if (variables.count(v.second) == 1) {//variable encontrada (ya existente) en el mapa
				variables[v.second]++;
			}	
			else {//la variable no se encuentra aun en el mapa
				variables[v.second] = 1; //insertamos la variable con valor 1
			}
		}
		else if (v.first == "GOTO") {
			//tambien se podr�a hacer con un iterador sobre "p" y el metodo find():
			//programa::const_iterator itPAux = p.find(stoi(v.second));
			//if (itPAux == p.end()){
			if (p.count(stoi(v.second)) == 0) {//si la linea no forma parte del programa
				error = true;
			}
			else {
				//salta a la instruccion de la linea v.second
				//itP = itPAux; //<- asi se haria con el iterador auxiliar
				itP = p.find(stoi(v.second));;
				GOTOok = true;
			}
		}
		n++;
		if (!GOTOok) {
			++itP;
		}	
	}
	return{ variables, error };
}


// Introduce el c�digo para tratar un caso de prueba. Devuelve true
// si se ha encontrado un caso de prueba en la entrada, o false si,
// en su lugar, se ha encontrado la marca de fin de fichero (EOF).

//Complejidad: O(N logM) siendo N y M los especificados en la funcion ejecutar
//Adem�s, a este NlogM habr�a que multiplicarle el numero de veces que se introduce la instruccion RUN, al cual llamaremos "t",
// quedando finalmente una complejidad de O(t* N logM)
bool tratar_caso() {
	string coso;
	programa map;
	while ((cin >> coso) && coso != "BYE" ){
		
		if (coso == "RUN") {//procesamos el RUN
			int N;
			cin >> N;

			auto [variablesMap, ok] = ejecutar(map, N);

			if (!ok) {
				for (const auto& [k, v] : variablesMap) {//O(M) siendo M el numero de variables del programa
					cout << k << " = " << v << "\n";
				}
				cout << "OK\n";
			}
			else cout << "ERROR\n";
		}
		else {//procesamos las instrucciones del programa
			int line = stoi(coso);
			string instr, vari;
			cin >> instr >> vari;

			pair<string, string> instruction = { instr, vari };
			map[line] = instruction;
		}
	}
	if (coso == "")
		return false;
	cout << "---\n";
	return true;
}


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

	// Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
	while (tratar_caso()) {}

	// Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
