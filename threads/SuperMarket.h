/* 
 * File:   SuperMarket.h
 * Author: amin
 *
 * Created on September 6, 2019, 4:32 PM
 */

#ifndef SUPERMARKET_H
#define	SUPERMARKET_H

#include "list.h"
#include "Customer.h"
#include "Cashier.h"

class SuperMarket {
public:
    static int peakHours[3]; //Peak hours are between 4 to 6 pm and random number of customers arriving for a check out is between 5 and 10 every minute.
    const static int maxCashiers=10;
    const static int minCashiers=2;
    SuperMarket();
    //SuperMarket(const SuperMarket& orig);
    virtual ~SuperMarket();
    bool isPeakHour(int);
    void addCustomer(Customer*);
    Cashier* openNewCashier();
    int getNumOfOpenCashiers();
    void run();
private:
    List<Cashier*> cashiers;
    List<Customer*> waitingQueue;
    List<Customer*> customers;
};

#endif	/* SUPERMARKET_H */

