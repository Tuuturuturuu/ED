/**
 * Implementaci�n del TAD Pila utilizando un vector din�mico
 * cuyo tama�o va creciendo si es necesario.
 * (c) Marco Antonio G�mez Mart�n, 2012
 * Modificado por Ignacio F�bregas
*/
#ifndef __STACK_H
#define __STACK_H

#include "Exceptions.h"
#include <iostream>
#include <iomanip>

/**
 * Implementaci�n del TAD Pila utilizando vectores din�micos.
 * Las operaciones son:
 *    - EmptyStack: -> Stack. Generadora implementada en el constructor sin par�metros.
 *    - push: Stack, Elem -> Stack. Generadora
 *    - pop: Stack - -> Stack. Modificadora parcial.
 *    - top: Stack - -> Elem. Observadora parcial.
 *    - empty: Stack -> Bool. Observadora.
 *    - size: Stack -> Entero. Observadora.
 */
template <class T>
class Stack {
public:

	/** Tama�o inicial del vector din�mico. */
	static const int TAM_INICIAL = 10;

	/** Constructor; operaci�n EmptyStack */
	Stack() {
		inicia();
	}

	/** Destructor; elimina el vector. */
	~Stack() {
		libera();
	}

	/**
	 * Apila un elemento. Operaci�n generadora.
	*/
	void push(const T& elem) {
		datos[numElems] = elem;
		numElems++;
		if (numElems == tam) //la pila est� llena, se ampl�a
			amplia();
	}

	/**
	 * Desapila un elemento. Operaci�n modificadora parcial, falla si la pila est� vac�a */
	void pop() {
		if (empty())
			throw EmptyStackException("Cannot pop. The stack is empty");
		--numElems;
	}

	/**
	 * Devuelve el elemento en la cima de la pila.
	 * Operaci�n observadora parcial, que falla si la pila est� vac�a.
	 */
	const T& top() const {
		if (empty())
			throw EmptyStackException("Cannot get top. The stack is empty");
		return datos[numElems - 1];
	}

	/** Devuelve true si la pila no tiene ning�n elemento. */
	bool empty() const {
		return numElems == 0;
	}

	/** Devuelve el n�mero de elementos que hay en la pila. */
	int size() const {
		return numElems;
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL A LA CLASE
	// //

	/** Constructor copia */
	Stack(const Stack<T>& other) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Stack<T>& operator=(const Stack<T>& other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Stack<T>& rhs) const {
		if (numElems != rhs.numElems)
			return false;
		bool iguales = true;
		for (unsigned int i = 0; i < numElems && iguales; ++i)
			if (datos[i] != rhs.datos[i])
				iguales = false;
		return iguales;
	}

	bool operator!=(const Stack<T>& rhs) const {
		return !(*this == rhs);
	}

	/** Escribe la pila en el flujo. Se usa desde operator<< */
	void write(std::ostream& sOut) {
		for (int i = numElems - 1; i >= 0; --i)
			sOut << "| " << std::setw(2) << std::left << datos[i] << "|" << std::endl;
		sOut << "|---|" << std::endl;
	}

protected:

	/** Crea un vector din�mico de tama�o inicial sin elementos */
	void inicia() {
		datos = new T[TAM_INICIAL];
		tam = TAM_INICIAL;
		numElems = 0;
	}

	void libera() {
		delete[]datos;
		datos = NULL;
	}

	void copia(const Stack& other) {
		tam = other.numElems + TAM_INICIAL;
		numElems = other.numElems;
		datos = new T[tam];
		for (unsigned int i = 0; i < numElems; ++i)
			datos[i] = other.datos[i];
	}

	/** Duplica el tama�o del vector de datos, copia sus elementos y libera memoria */
	void amplia() {
		T* viejo = datos;
		tam *= 2;
		datos = new T[tam];
		for (unsigned int i = 0; i < numElems; ++i)
			datos[i] = viejo[i];

		delete[]viejo;
	}

private:

	/** Puntero al array que contiene los datos. */
	T* datos;

	/** Tama�o del vector datos. */
	unsigned int tam;

	/** N�mero de elementos reales guardados. */
	unsigned int numElems;
};

/** Operador de escritura */
template<class T>
std::ostream& operator<<(std::ostream& sOut, Stack<T>& s) {
	s.write(sOut);
	return sOut;
}


#endif // __STACK_H

