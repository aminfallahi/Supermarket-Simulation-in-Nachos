/* 
 * File:   Customer.h
 * Author: amin
 *
 * Created on September 6, 2019, 4:32 PM
 */

#ifndef CUSTOMER_H
#define	CUSTOMER_H


class Customer {
public:
    Customer();
    //Customer(const Customer& orig);
    virtual ~Customer();
    static int lastId;
    void setNumOfItems(int);
    int getNumOfItems();
    int getTimeProcessed();
    void incrementTimeProcessed();
    void incrementWaitTime();
    friend bool operator==(const Customer&,const Customer&);
    int getId();
    void setDone();
    bool isDone();
    int getWaitTime();
private:
    int numOfItems; //Customers, checking out have a random number of items, average range between 5 to 40 items.
    int timeProcessed; //Time in front of line in seconds=SERVICE TIME
    int id;
    int waitTime;
    bool done;
};

#endif	/* CUSTOMER_H */

