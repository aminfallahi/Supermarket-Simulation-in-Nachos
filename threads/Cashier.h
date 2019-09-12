/* 
 * File:   Cashier.h
 * Author: amin
 *
 * Created on September 6, 2019, 4:32 PM
 */

#ifndef CASHIER_H
#define	CASHIER_H

#include "Customer.h"
#include "list.h"

class Cashier {
public:
    const static int scanTime = 5; //A cashier takes an average of 5 seconds to scan a single item for a customer.
    const static int startUpTime = 10; //The average startup time for a check out (greeting a new customer, moving the conveyer belt to reach items, …) is 10 seconds.
    const static int closeTime = 90; //The average close time for a check out (getting the total, handling coupons, getting payments, …) is 1.5 minute.
    const static int maxCustomers = 5; //During regular hours customers between 0 and 5 arrive every minute.
    static int lastId;
    Cashier();
    //Cashier(const Cashier& orig);
    virtual ~Cashier();
    bool isOpen();
    void open();
    void close();
    void addCustomer(Customer*);
    bool removeCustomer(Customer*);
    bool hasRoom();
    void run();
    bool isEmpty();
    friend bool operator==(const Cashier&,const Cashier&);
    int getId();
    int getNumInLine();
    void resetMoreThan3Time(); //FOR STATS
    int getMoreThan3Time(); //FOR STATS
    
private:
    bool status; //open or close
    List<Customer*> line;
    int id;
    int numInLine;
    int moreThan3Time; //FOR STATS
};

#endif	/* CASHIER_H */

