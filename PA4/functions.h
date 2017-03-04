/*
 * PA4 -- Yizhen Wang, Yuan Wang
 * ywang22 ywang19
 * functions.h
 * Author: student
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

int getShortestLine();
int increment(int place);
int decriment(int place);
int getVal(int place);
void addUsers(EventQueue* eq, int cc, int max);
void printCustomers(int queue);
int totalcustomers();
void runMultiQueueSimulation();
void runUniQueueSimulation();
void instMax(int a);
double mean(int* list, int count);
double standardDeviation(int* list, int count);


#endif /* FUNCTIONS_H_*/
