#ifndef DATE2_H_
#define DATE2_H_

#include "Error.h"

// TAD Fecha representado como <dia,mes,año> con POO (encapsulación+privacidad)

class TDate2{
	private:
		int day;
		int month;
		int year;

		int daysInMonth(int m) const;
		int calculateValue() const;
		bool correctDate() const;

	public:
		TDate2(int d,int m,int y); // throws Error
		//TDate2(const TDate2& date);
		void operator++();
		void operator+=(int n);
		int diff(const TDate2& date) const;
		void print() const;


};



#endif /* DATE2_H_ */
