#include <iostream>

using namespace std;

#include "SetTests.h"
#include "Error.h"
#include "SetOfInts1.h"
#include "SetOfInts2.h"
#include "SetOfInts3.h"
#include "Set.h"

void testSetOfInts(){
	char op;
	int n;
	SetOfInts1 set = SetOfInts1();
	SetOfInts1 set2 = set;
    cin >> set;

	//cin >> set;
	cout << set << endl;
	do{
		cout << "Choose option ((a)dd, (r)emove, (j)oin, (i)ntersect, "
				"(c)ontains, (e)xit)" << endl;
		cin >> op;
		if (op == 'a'){
			cin >> n;
			try {
				set.add(n);
			} catch (Error& e){
				cout << e.getMessage() << endl;
			}
		} else if (op == 'j') {
			cin >> set2;
			try {
				set.join(set2);
			} catch (Error& e) {
				cout << e.getMessage() << endl;
			}
		} else if (op == 'i') {
			cin >> set2;
			set.intersect(set2);
		} else if(op == 'r'){
			cin >> n;
			set.remove(n);
		} else if(op == 'c'){
			cin >> n;
			cout << set.contains(n) << endl;
		}
		cout << set << endl;
	} while (op != 'e');
	cout << "Program finished" << endl;
}

void testGenericSet(){
	char op;
	string n;
	Set<string> set = Set<string>();
	cin >> set;
	Set<string> set2 = set; // llama al constructor por copia
	cout << set << endl;
	do{
		cout << "Choose option ((a)dd, (r)emove, (c)ontains, (e)xit)" << endl;
		cin >> op;
		if (op == 'a'){
			cin >> n;
			try {
				set.add(n);
			} catch (Error& e){
				cout << e.getMessage() << endl;
			}
		} else if(op == 'r'){
			cin >> n;
			set.remove(n);
		} else if(op == 'c'){
			cin >> n;
			cout << set.contains(n) << endl;
		}
		cout << set << endl;
	} while (op != 'e');
	cout << "Program finished" << endl;
}

/*int valueOfInt(const int& n){
	return n%10;
}

int valueOfInt2(const int& n){
	if ((n >= 0) && (n < 10))
		return n;
	else throw Error("Integer out of range");
}

int valueOfLetter(const char& c){
	int n = c - 'a';
	if ((n >= 0) && (n < 26))
		return n;
	else throw Error("Invalid character");
}

void testSmallSet() {
	//SmallSet<int, 9, valueOfInt2> set;
	//SmallSet<int, 9, valueOfInt2> set2;
	SmallSet<char, 25, valueOfLetter> set;
	SmallSet<char, 25, valueOfLetter> set2;
	char op;
	// int n;
	char n;
	try {
		cin >> set;
	} catch (Error& e) {
		cout << e.getMessage() << endl;
	}
	cout << set << endl;
	do {
		cout << "Choose option ((a)dd, (r)emove, (j)oin, (i)ntersect, "
			"(c)ontains, (s)ize, (e)xit)" << endl;
		cin >> op;
		try {
			if (op == 'a') {
				cin >> n;
				set.add(n);
			} else if (op == 'j') {
				//set2;
				cin >> set2;
				set.join(set2);
			} else if (op == 'i') {
				cin >> set2;
				set.intersect(set2);
			} else if (op == 'r') {
				cin >> n;
				set.remove(n);
			} else if (op == 's') {
				cout << set.size() << endl;
			} else if (op == 'c') {
				cin >> n;
				cout << set.contains(n) << endl;
			}
		} catch (Error& e) {
			cout << e.getMessage() << endl;
		}
		cout << set << endl;
	} while (op != 'e');
	cout << "Program finished" << endl;
}
*/
