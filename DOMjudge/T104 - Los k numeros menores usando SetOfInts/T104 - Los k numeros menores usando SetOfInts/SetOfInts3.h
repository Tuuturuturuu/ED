
#ifndef SETOFINTS3_H_
#define SETOFINTS3_H_

#include "Error.h"

class SetOfInts3 {
	// Conjuntos de enteros representados como array estáticos ordenados sin repeticiones
private:
	static const int MAXSIZE = 75;

	int elems[MAXSIZE];
	int _size;

	bool isFull() const;
	void binSearch(int x, bool& found, int& pos) const;
	int binSearchAux(int x, int a, int b) const;
	void shiftRightFrom(int i);
	void shiftLeftFrom(int i);

public:
	SetOfInts3();
	int size();
	bool isEmpty() const;
	void add(int x); //throws Error
	bool contains(int x) const;
	void remove(int x);
	void join(const SetOfInts3& set);
	void intersect(const SetOfInts3& set);
	friend istream& operator>>(istream& sIn, SetOfInts3& set);
	friend ostream& operator<<(ostream& sOut, SetOfInts3& set);

	//añadidos:
	int getMax() const;
	void removeMax();
	int getMin() const;
	void removeMin();
};

#endif /* SETOFINTS3_H_ */
