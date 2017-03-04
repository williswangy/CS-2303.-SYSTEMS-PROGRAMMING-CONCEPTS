/*
 * calculator.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: student
 */

//#include "main.h"

#include <iostream>
#include "Rational.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;
//namespace std {



void calculate(std::ifstream &in){


	string perline; //read in each line of input file
	while(getline(in, perline)) {

		stack<Rational> s; // stack used to store numbers
		stringstream line(perline); // turn "perline" into readable stream

		string nod; // seperate line into nod

		bool isBoolean = false, warn = false, result;
		// isBoolean to indicate whether there are any boolean operator in this line
		// warn to indicate whether there is any invalid input in this line and print out warning
		// result is used to print out boolean result

		while(line >> nod) { // seperate each line into nod

			if(warn) { // if warn, immediately break the loop;
				break;
			}

			if(!isBoolean) {
			// is there are already boolean operator has been calculated
			// then there is must be something wrong
			// since there cannot be any legal calculation after a boolean operator


				if(nod == "+") {
					if(s.size() > 1){ // check the size of the stack to make sure we have enough operands
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						s.push(r1 + r2);
					}
					else{ // if not enough operands, warning
						warn = true;
					}
				}else if(nod == "-") {
					if(s.size() > 1) {
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						s.push(r1 - r2);
					}
					else{
						warn = true;
					}
				}else if(nod == "*") {
					if(s.size() > 1) {
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						s.push(r1 * r2);
					}
					else{
						warn = true;
					}
				}else if(nod == "/") {
					if(s.size() > 1) {
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						if(r2.getNum() == 0) { //this one will make sure that zero is not used as denominator
							warn = true;
						}
						else{
							s.push(r1 / r2);
						}
					}
					else{
						warn = true;
					}


					//boolean operator

				}else if(nod == ">") {
					if(s.size() > 1){
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						result = r1 > r2; // result of boolean operation between rational numbers
						isBoolean = true; // one boolean operator has already appeared, no more is allowed
					}
					else{ warn = true; }
				}else if(nod == "<") {
					if(s.size() > 1){
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						result = r1 < r2;
						isBoolean = true;
					}else {warn = true;}
				}else if(nod == ">=") {
					if(s.size() > 1){
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						result = r1 >= r2;
						isBoolean = true;
					}else {warn = true;}
				}else if(nod == "<=") {
					if(s.size() > 1){
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						result = r1 <= r2;
						isBoolean = true;
					} else{warn = true;}
				}else if(nod == "!=") {
					if(s.size() > 1){
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						result = r1 != r2;
						isBoolean = true;
					} else{warn = true;}
				}else if(nod == "==") {
					if(s.size() > 1){
						Rational r2(s.top());
						s.pop();
						Rational r1(s.top());
						s.pop();
						result = r1 == r2;
						isBoolean = true;
					} else{ warn = true;}
				}else { // is the nod is not an operator, then it is a rational number, store it in stack
					Rational r; //declare this rational number
					stringstream theRational(nod); // turn the nod into stringstream to read it
					char check;
					check = theRational.peek(); // check whether this nod is something not a digit or negative sign
					if(!isdigit(check) && check != '-') {
						warn = true; // if wrong, warning and break the loop;
						break;
					}
						theRational >> r;

					if(r.getDenom() == 0) {
						warn = true; // is the rational number has 0 as the denominator, warning and break;
					}
					else{
						s.push(r); // put this rational number on the top of the stack
					}
				}

			}else {
				warn = true;
				//if the loop execute again after one boolean operator appears,
				//warning and break;
			}


		}

		cout << perline; // print out the original line appear in the file
		if(s.size() > 0 && isBoolean) {
			warn = true;
		}

		if(s.size() > 1) {
			warn = true;
		}

		if(warn) { // if warning, then warning
			cout << "\t:" << "Warning: Invalid Input" << endl;
		}
		else{ // is not warning, then print out the result
			if(!isBoolean){ // if is not a boolean operator, then print the arithmetic result
				Rational R = s.top();
				cout << "\t:" << R << " " << "(" << "double" << " " << R.toDouble() << ")" << endl;
			}
			else{ // if it is a boolean operator, then print out the boolean result
				cout << "\t:" << boolalpha << " " << result << endl;
			}
		}
	}
}

int main(int argc, char* argv[]) {

	if(argc < 2) { // check whether have had enough input to read file in
		cout << "INVALID ARGUMENTS";
		return 0;
	}

	// cycle through all input file
	for(int i = 1; i < argc; i++) {
		ifstream in(argv[i]);
		cout << "\nNo." << i << '\n';
		cout << '\n' << "File :" << argv[i] << '\n' << endl;

		if(in) { // check whethe the argument is valid
			calculate(in);
			in.close(); // close the file
		}else{
			cout << "Warning: File Not Found\n"; // if file not found, warning
		}
		cout << "run" << i;
	}

	return 0;
}
//} /* namespace std */
