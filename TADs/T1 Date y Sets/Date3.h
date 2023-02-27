#ifndef DATE3_H_
#define DATE3_H_

#include "Error.h"

// TAD Fecha representado como un valor (días pasados desde una fecha origen) con POO (encapsulación+privacidad)

class TDate3{
	// Fechas representadas con un solo entero que guarda el nº de días transcurridos
	// desde la fecha 1/1/1

	private:
		int value;

		int daysInMonth(int m) const;
		void calculateDMY(int& day,int& month,int& year) const;
		bool correctDate(int day,int month,int year) const;

	public:
        TDate3();
		TDate3(int d,int m,int y); //throws Error
		TDate3(const TDate3& date);
		void operator++();
		void operator+=(int n);
		int diff(const TDate3& date) const;
		void print() const;
};


#endif /* DATE3_H_ */
