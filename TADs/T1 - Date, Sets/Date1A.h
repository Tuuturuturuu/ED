
#ifndef DATE1A_H_
#define DATE1A_H_

#include "Error.h"

// TAD Fecha representado como <dia,mes,año> sin encapsulación ni privacidad (no orientación a objetos)

typedef struct {
	int day;
	int month;
	int year;
} TDate1A;


// Public operations
TDate1A newDate1A(int d,int m,int y); // throws Error
TDate1A incr(const TDate1A& date);
int diff(const TDate1A& date,const TDate1A& date_p);
void print(const TDate1A& date);


// Private operations
int calculateValue(const TDate1A& date);
int daysInMonth(int m);
bool correctDate1A(int d,int m,int y);


#endif /* DATE1A_H_ */
