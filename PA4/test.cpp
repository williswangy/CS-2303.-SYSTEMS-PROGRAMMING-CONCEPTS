/*
 * PA -- Yizhen Wang, Yuan Wang
 * ywang22 ywang19
 * test.cpp
 * Author: student
 */

#include "Event.h"
#include "functions.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>

using namespace std;

int customers;
int tellers;
int simTime;   //simulationTome (seconds)
int ast;       //averageServiceTime
int *queues;
int clck = 0;

int idleTime = 0;
int serviceTime = 0;

int *startTimes;
int pos = 0;
int inspos = 0;
int maxTime = 0;
int uni = 0;
int DEBUG = 0;



int main(int argc, char*argv[]){
    customers = atoi(argv[1]);  //number of the customers
    tellers = atoi(argv[2]);    //number of the tellers
    simTime = 60*atoi(argv[3]); //simulationTome (seconds)
    ast = atoi(argv[4]);        //averageServiceTime

    if (argc >= 6)
    {
        srand(atoi(argv[5]));
        if (argc >= 7)
        {
            DEBUG = atoi(argv[6]);
        }
    }
    else
    {
        int a = time(NULL);
        srand(a);
    }

    runMultiQueueSimulation();
    runUniQueueSimulation();
}


void runMultiQueueSimulation()
{
    idleTime = 0;
    serviceTime = 0;
    maxTime = 0;
    pos = 0;
    queues = (int *) malloc(tellers * sizeof(int));
    startTimes = (int *) malloc(customers * sizeof(int));
    TellerEvent* a = new TellerEvent(0);
    a->setTime(120);
    EventQueue eq(a);
    for(int i = 1; i < tellers; i++)
    {
        TellerEvent* a = new TellerEvent(i);
        a->setTime(0);
        eq.insert(a);
    }
    addUsers(&eq, customers, simTime);
    while(eq.hasNext())
    {
        clck = eq.getData()->getTime();
        if (DEBUG) cout << "Event time: " << clck << endl;
        eq.getData()->onCompletion(&eq);
        if (DEBUG) printCustomers(tellers);
        eq = *(eq.next);
        if (DEBUG) getchar();
    }

    cout << "MULTI QUEUE" << endl;
    cout << "   # " << "there were " << customers << " customers served" << endl;
    cout << "   # " << "it took " << clck << " seconds to serve all the customers" << endl;
    cout << "   # " << "there were " << tellers << " tellers in a multi-queue system" << endl;
    cout << "   # " << "the customers were in the bank for an average of " << mean(startTimes, customers) << " seconds" << endl;
    cout << "   # " << "with a standard deviation of " << standardDeviation(startTimes, customers) << " seconds" << endl;
    cout << "   # " << "the longest time a customer waited in line was: " << maxTime << " seconds" << endl;
    cout << "   # " << "the total teller idle time was " << idleTime << endl;
    cout << "   # " << "and the total service time was " << serviceTime << endl;
    cout << endl;
    
    free(queues);
    free(startTimes);
}


void runUniQueueSimulation()
{
    idleTime = 0;
    serviceTime = 0;
    maxTime = 0;
    pos = 0;
    inspos = 0;
    uni = 1;
    queues = (int *) malloc(1 * sizeof(int));
    startTimes = (int *) malloc(customers * sizeof(int));


    TellerEvent* a = new TellerEvent(0);
    a->setTime(120);
    EventQueue eq(a);
    for(int i = 1; i < tellers; i++)
    {
        TellerEvent* a = new TellerEvent(0);
        a->setTime(0);
        eq.insert(a);
    }

    addUsers(&eq, customers, simTime);
    while(eq.hasNext())
    {
        clck = eq.getData()->getTime();
        if (DEBUG) cout << "Event time: " << clck << endl;
        eq.getData()->onCompletion(&eq);
        if (DEBUG) printCustomers(tellers);
        eq = *(eq.next);
        if (DEBUG) getchar();
    }


    cout << "SINGLE QUEUE" << endl;
    cout << "   # " << "there were " << customers << " customers served" << endl;
    cout << "   # " << "it took " << clck << " seconds to serve all the customers" << endl;
    cout << "   # " << "there were " << tellers << " tellers in a multi-queue system" << endl;
    cout << "   # " << "the customers were in the bank for an average of " << mean(startTimes, customers) << " seconds" << endl;
    cout << "   # " << "with a standard deviation of " << standardDeviation(startTimes, customers) << " seconds" << endl;
    cout << "   # " << "the longest time a customer waited in line was: " << maxTime << " seconds" << endl;
    cout << "   # " << "the total teller idle time was " << idleTime << endl;
    cout << "   # " << "and the total service time was " << serviceTime << endl;
    cout << endl;
    
    free(queues);
    free(startTimes);
}












//action method for TellerEvent
void TellerEvent::onCompletion(EventQueue* e)
{
    if (clck > simTime && totalcustomers() <= 0)
    {
        //dont do anything
    }
    else if (getVal(queue) <= 0)
    { //there is nobody in line!
        TellerEvent* te = new TellerEvent(queue);
        int ra = 151+rand()%150;
        te->setTime(clck+ra);
        e->insert(te);
        if (DEBUG) cout << "Due to lack of customers, the teller in queue " << queue << " has gone idle for " << ra << " seconds" << endl;
        idleTime += ra;
    }
    else
    { //there is a customer in line
        instMax(clck-startTimes[pos]);
        int ra = rand()%ast;
        if (DEBUG) cout << "this "<<pos<<"th customer entered the bank at time: " << startTimes[pos] << endl;
        startTimes[pos] = clck+ra-startTimes[pos];
        if (DEBUG) cout << "this customer was in the bank for " << startTimes[pos] << " seconds" << endl;
        CustomerEvent* ce = new CustomerEvent(1, queue, pos);
        pos++;
        ce->setTime(ra+clck);
        e->insert(ce);
        if (DEBUG) cout << "a customer in queue " << queue << " is being serviced by the bank" << endl;
        if (DEBUG) cout << "    this will take " << ra << " seconds" << endl;
        serviceTime += ra;
        decriment(queue);
    }
}

//action method for CustomerEvent
void CustomerEvent::onCompletion(EventQueue* e)
{
    if (type == 0)
    { //entering
        increment(getShortestLine());
        startTimes[inspos] = clck;
        if (DEBUG) cout << "a new customer has entered with id "<<inspos<<" into queue " << getShortestLine() << endl;
        inspos++;
    }
    else
    { //leaving
        TellerEvent* te = new TellerEvent(queue);
        te->setTime(clck);
        e->insert(te);
        if (DEBUG) cout << "a customer has left the bank" << endl;
        if (DEBUG) cout << "there are " << getVal(queue) << " customers in line " << queue << endl;
    }
}
//action method for BankEvent
void BankEvent::onCompletion(EventQueue* e)
{
    cout << "this should never be called!" << endl;
}

//maxtime
void instMax(int a)
{
    if (a > maxTime)
    {
        maxTime = a;
    }
}


//total customers
int totalcustomers()
{
    int tot = 0;
    for(int i = 1; i < tellers; i++)
    {
        tot += getVal(i);
    }
    return tot;
}

//shortestLine
int getShortestLine()
{
    if (uni)return 0;
    int minVal= *queues;
    int minPla=0;
    for(int i = 1; i < tellers; i++)
    {
        if (*(queues+i) < minVal)
        {
            minVal = *(queues+1);
            minPla = i;
        }
    }
    return minPla;
}
//+
int increment(int place)
{
    queues[place]++;
    return getVal(place);
}

//-
int decriment(int place)
{
    queues[place]--;
    return getVal(place);
}

//get value
int getVal(int place)
{
    return queues[place];
}
//add users
void addUsers(EventQueue* eq, int cc, int max)
{
    for(int i = 0; i < cc; i++)
    {
        int r = rand() % max;
        CustomerEvent* a = new CustomerEvent(0,0,i);
        a->setTime(r);
        eq->insert(a);
    }
}


//Customers for print
void printCustomers(int queuez)
{
    cout << "Customers: " << endl;
    for(int i = 0; i < queuez; i++)
    {
        cout << "  " << i << "|";
        for(int j = 0; j < getVal(i); j++)
        {
            cout << "x";
        }
        cout << endl;
    }
    

}

//mean
double mean(int* list, int count)
{
    double total = 0;
    for(int i = 0; i < count; i++)
    {
        total += list[i];
    }
    return total/count;
}

//sd
double standardDeviation(int* list, int count)
{
    double m = mean(list, count);
    double t = 0;
    for(int i = 0; i < count; i++)
    {
        t += (m-list[i]) * (m-list[i]);
    }
    return sqrt(t / count);
}
