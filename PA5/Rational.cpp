/*
 * Rational.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: student
 */

#include "Rational.h"
#include <iostream>

using namespace std;


//constructor
Rational::Rational() {
	this->num = 0;
	this->denom = 1;
}

Rational::Rational(int a) {
	num = a;
	denom = 1;
	// TODO Auto-generated constructor stub

}

Rational::Rational(int a, int b) {
	num = a;
	denom = b;
}


//set numerator and denominator
// and get numerator and denominator
void Rational::setNum(int a) {
	num = a;
}

void Rational::setDenom(int a) {
	denom = a;
}

int Rational::getNum() {
	return num;
}

int Rational::getDenom() {
	return denom;
}


//normalize a rational number
void Rational::normalize() {
	int c = gcd(this->num, this->denom);
	this->num = this->num/c;
	this->denom = this->denom/c;
	if(this->num > 0 && this->denom < 0){
		this->num = -this->num;
		this->denom = -this->denom;
	}
}

//find the greatest common divisor
int Rational::gcd(int a, int b) {
	int temp;
	while(b) {
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}


/*
void Rational::normalize() {
	int gcd = gcd(this -> num, this -> denom);
	this->setNum(this -> num / gcd);
	this->setDenom(this -> denom / gcd);
}
*/

//turn a rational number to double form
double Rational::toDouble() {
	return ((double)num / (double)denom);
}

//overloading operator to satisfy rational number
Rational Rational::operator +(Rational r) {
	Rational temp(num*r.denom + denom*r.num, denom*r.denom);
	temp.normalize();
	return temp;
}

Rational Rational::operator -(Rational r) {
	Rational temp(num*r.denom - denom*r.num, denom*r.denom);
	temp.normalize();
	return temp;
}

Rational Rational::operator *(Rational r) {
	Rational temp(num*r.num, denom*r.denom);
	temp.normalize();
	return temp;
}

Rational Rational::operator /(Rational r) {
	Rational temp(num*r.denom, denom*r.num);
	temp.normalize();
	return temp;
}

int Rational::operator <(Rational r) {
	return num*r.denom < denom*r.num;
}

int Rational::operator >(Rational r) {
	return num*r.denom > denom*r.num;
}

int Rational::operator <=(Rational r) {
	return num*r.denom <= denom*r.num;
}

int Rational::operator >=(Rational r) {
	return num*r.denom >= denom*r.num;
}

int Rational::operator ==(Rational r) {
	return num*r.denom == denom*r.num;
}

int Rational::operator !=(Rational r) {
	return num*r.denom != denom*r.num;
}


//overload the readin and putout operator
istream &operator >> (istream &is, Rational &r) {
	char c;
	is >> r.num;
	is.get(c);
	if(c == ' ') {
		r.denom = 1;
	}else if (c == '/') {
		is >> r.denom;
	}
	r.normalize();
	return is;

}

ostream &operator << (ostream &os, Rational &r) {
	if(r.denom == 1) {
		return os << r.num;
	} else {
		return os << r.num << '/' << r.denom;
	}
}

//destroctor
Rational::~Rational() {
	// TODO Auto-generated destructor stub
}

