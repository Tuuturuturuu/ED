#include <iostream>
using namespace std;

#include "Error.h"
#include "SetOfInts3.h"


// Constructors

SetOfInts3::SetOfInts3() {
	_size = 0;
}

// Public methods
int SetOfInts3::getMax() const { //o(1) constante
	return elems[_size-1];
}

int SetOfInts3::getMin() const { //o(1) constante
	return elems[0];
}

void SetOfInts3::removeMax() {
	_size--;
}

void SetOfInts3::removeMin() {
	shiftLeftFrom(0);//O(n)
	_size--;
}




bool SetOfInts3::isEmpty() const {
	return (_size == 0);
}

//O(n)
void SetOfInts3::add(int x) { //throws Error
	bool found;
	int pos;

	binSearch(x, found, pos); //O(log n)
	if (!found) {
		if (isFull())
			throw Error("Cannot add: The set is full");
		else {
			shiftRightFrom(pos + 1); //O(n)
			elems[pos + 1] = x; //O(1)
			_size++;
		}
	}
}

void SetOfInts3::remove(int x) {
	bool found;
	int pos;

	binSearch(x, found, pos);//O(log n)
	if (found) {
		shiftLeftFrom(pos);//O(n)
		_size--;
	}
}

bool SetOfInts3::contains(int x) const {
	bool found;
	int pos;

	binSearch(x, found, pos);
	return found;
}

void SetOfInts3::join(const SetOfInts3& set) {
	throw Error("Join operation not supported");
}

void SetOfInts3::intersect(const SetOfInts3& set) {
	throw Error("Intersection operation not supported");
}

istream& operator>>(istream& sIn, SetOfInts3& set) {
	int n;
	int d;
	sIn >> n;
	//substr
	set._size = 0;
	if (sIn.fail()) return sIn;
	for (int i = 0; i < n; i++) {
		sIn >> d;
		set.add(d);
	}
	return sIn;
}

ostream& operator<<(ostream& sOut, SetOfInts3& set) {
	//sOut << "{";
	for (int i = 0; i < set._size - 1; i++)
		sOut << set.elems[i] << " ";
	if (set._size > 0) sOut << set.elems[set._size - 1];
	//sOut << "}";
	return sOut;
}


// Private methods

bool SetOfInts3::isFull() const {
	return _size == MAXSIZE;
}

int SetOfInts3::size()
{
	return this->_size;
}

int SetOfInts3::binSearchAux(int x, int a, int b) const {
	// Pre: elems est� ordenado entre 0 .. size-1
	//      ( 0 <= a <= size ) && ( -1 <= b <= size ) && ( a <= b+1 )
	//      todos los elementos a la izquierda de 'a' son <= x
	//      todos los elementos a la derecha de 'b' son > x

	int p, m;

	if (a == b + 1)
		p = a - 1;
	else if (a <= b) {
		m = (a + b) / 2;
		if (elems[m] <= x)
			p = binSearchAux(x, m + 1, b);
		else
			p = binSearchAux(x, a, m - 1);
	}
	return p;
	// Post: devuelve el mayor �ndice i (0 <= i <= size-1) que cumple
	//       elems[i] <= x
	//       si x es menor que todos los elementos de elems, devuelve -1
}

void SetOfInts3::binSearch(int x, bool& found, int& pos) const {
	// Pre: los size primeros elementos de elems est�n ordenados
	//      size >= 0

	pos = binSearchAux(x, 0, _size - 1);
	found = (pos >= 0) && (pos < _size) && (elems[pos] == x);

	// Post : devuelve el mayor �ndice i (0 <= i <= size-1) que cumple
	//        elems[i] <= x
	//        si x es menor que todos los elementos de elems, devuelve -1
	//        found es true si x esta en elems[0..size-1]
}

void SetOfInts3::shiftRightFrom(int i) {
	for (int j = _size; j > i; j--)
		elems[j] = elems[j - 1];
}

void SetOfInts3::shiftLeftFrom(int i) {
	for (; i < _size - 1; i++)
		elems[i] = elems[i + 1];
}


