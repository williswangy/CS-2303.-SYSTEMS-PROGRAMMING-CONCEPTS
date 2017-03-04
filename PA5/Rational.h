/*
 * Rational.h
 *
 *  Created on: Feb 19, 2017
 *      Author: student
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <fstream>
#include <iostream>
using std::ostream;
using std::istream;


// the class to store rational number
class Rational {
	friend ostream &operator << (ostream &output, Rational&A);
	friend istream &operator >> (istream &input, Rational&A);



private:
	int num;
	int denom;
	int gcd(int a, int b);



public:
	void normalize();
	Rational operator+ (const Rational);
	Rational operator- (const Rational);
	Rational operator* (const Rational);
	Rational operator/ (const Rational);

	int operator> (const Rational);
	int operator< (const Rational);
	int operator>= (const Rational);
	int operator<= (const Rational);
	int operator== (const Rational);
	int operator!= (const Rational);

	double toDouble();
	Rational();
	Rational(int a);
	Rational(int a, int b);
	virtual ~Rational();

	void setNum(int a);
	void setDenom(int a);
	int getNum();
	int getDenom();
};

#endif /* RATIONAL_H_ */
