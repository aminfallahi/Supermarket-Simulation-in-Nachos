#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "list.h"
#include "Cashier.h"
#include "SuperMarket.h"
#include <stdlib.h>
#include <time.h>
#include "Customer.h"

/*class bbb{
		friend bool operator==(const bbb &b1,const bbb &b2){
		return true;
	}
};
class blah{
public:
	int id;
	blah(){};
	blah(int i){
		id=i;
	}
	friend bool operator==(const blah &b1,const blah &b2){
		return b1.id==b2.id;
	}
	List<bbb> hhh;
};
 */
void
runSuperMarket()
{
	/*Cashier c1,c2;
	blah b1(1);
	blah b2(2);
	printf("%d %d",c1.getId(),c2.getId());
	if (c1==c2)
		printf("yes");
	printf("hello\n");
	List<blah> hello;
		printf("1212hello\n");

	hello.Append(b1);
	hello.Append(b2);
	printf("%d\n", hello.RemoveFront());
	printf("%d\n", hello.RemoveFront());
	printf("sss");*/
	//t->Fork((VoidFunctionPtr) runSM);
	SuperMarket sm;
	srand(time(NULL));
	Customer::lastId = 0;

	List<Customer*> Customers;


	int hour, minute, second, i, custNum, custSec;

	for (hour = 2; hour <= 7; hour++) {
		int sumCust = 0;
		int sumWaitTime = 0;
		int sumServTime = 0;
		int minWaitTime = 10000;
		int maxWaitTime = 0;
		int minServTime = 10000;
		int maxServTime = 0;
		List<Customer*> hourCustomers;

		for (minute = 0; minute < 60; minute++) {

			if (sm.isPeakHour(hour))
				custNum = rand() % 6 + 5; //peak hours 5-10 customers per minute
			else
				custNum = rand() % 6; //reg hours 0-5 customers per minute
			if (custNum > 0)
				custSec = 60 / custNum;
			printf("Hour is %d cust num is %d\n", hour, custNum);
			for (second = 0; second < 60; second++) {
				if (custNum != 0 and second % custSec == 0) {
					sumCust++;
					Customer* cust = new Customer; //create new customer
					Customers.Append(cust);
					hourCustomers.Append(cust);
					cust->setNumOfItems(rand() % 36 + 5);

					sm.addCustomer(cust);
				}
				//run each cashier for one second
				sm.run();
				//
			}
			int a;
			//scanf("%d",&a);
		}
		ListIterator<Customer*> custIter(&hourCustomers);
		for (; !custIter.IsDone(); custIter.Next()) {
			int wt = custIter.Item()->getWaitTime();
			int st = custIter.Item()->getTimeProcessed();
			sumWaitTime += wt;
			sumServTime += st;
			minWaitTime = (minWaitTime < wt) ? minWaitTime : wt;
			maxWaitTime = (maxWaitTime < wt) ? wt : maxWaitTime;
			minServTime = (minServTime < st) ? minServTime : st;
			maxServTime = (maxServTime < st) ? st : maxServTime;
		}
		printf("Hour %d; Average number of customers arriving for checkout: %d; avg/min/max wait time: %d/%d/%d; avg/min/max service time: %d/%d/%d\n", hour, sumCust / 60, sumWaitTime / sumCust, minWaitTime, maxWaitTime, sumServTime / sumCust, minServTime, maxServTime);

	}
}
