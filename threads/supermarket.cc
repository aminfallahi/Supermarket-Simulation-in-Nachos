#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "list.h"
#include "Cashier.h"
#include "SuperMarket.h"
#include <stdlib.h>
#include <time.h>
#include "Customer.h"

void
runSuperMarket()
{
	SuperMarket sm;
	srand(time(NULL));
	Customer::lastId = 0;

	List<Customer*> Customers;


	int hour, minute, second, i, custNum, custSec;

	//FOR STATS
	int sumWaitTimeAll = 0, minWaitTimeAll = 10000, maxWaitTimeAll = 0,
		sumServTimeAll = 0, minServTimeAll = 10000, maxServTimeAll = 0,
		maxWaitingQueueAll = 0;

	for (hour = 2; hour <= 7; hour++) {

		//FOR STATS
		int sumCust = 0,
			sumWaitTime = 0, minWaitTime = 10000, maxWaitTime = 0,
			sumServTime = 0, minServTime = 10000, maxServTime = 0,
			sumOpenLines = 0, maxOpenLines = 0,
			sumWaitingQueue = 0, minWaitingQueue = 10000, maxWaitingQueue = 0;

		//this is to keep track of customers who have entered the supermarket during current hour
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
			}

			//FOR STATS: calculating output numbers
			int oc = sm.getNumOfOpenCashiers();
			sumOpenLines += oc;
			maxOpenLines = (maxOpenLines < oc) ? oc : maxOpenLines;
			int wq = sm.getWaitingQueueSize();
			sumWaitingQueue += wq;
			minWaitingQueue = (minWaitingQueue < wq) ? minWaitingQueue : wq;
			maxWaitingQueue = (maxWaitingQueue < wq) ? wq : maxWaitingQueue;
			maxWaitingQueueAll = (maxWaitingQueueAll < wq) ? wq : maxWaitingQueueAll;

		}

		//FOR STATS: calculating output numbers
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

		int* moreThan3 = sm.getCashiersStats();
		printf("Hour %d; Cashier stats: ", hour);
		int i;
		for (i = 0; i < 10; i++) {
			printf("%d ", moreThan3[i]);
		}

		printf("Hour %d; Average number of customers arriving for checkout: %d; "
			"avg/min/max wait time: %d/%d/%d; "
			"avg/min/max service time: %d/%d/%d "
			"avg open lines: %d; "
			"max open lines: %d; "
			"avg/min/max waiting queue size: %d/%d/%d\n",
			hour, sumCust / 60,
			sumWaitTime / sumCust, minWaitTime, maxWaitTime,
			sumServTime / sumCust, minServTime, maxServTime,
			sumOpenLines / 60,
			maxOpenLines,
			sumWaitingQueue / 60, minWaitingQueue, maxWaitingQueue);

	}

	//FOR STATS: calculating output numbers
	ListIterator<Customer*> custIter(&Customers);
	for (; !custIter.IsDone(); custIter.Next()) {
		int wt = custIter.Item()->getWaitTime();
		int st = custIter.Item()->getTimeProcessed();
		sumWaitTimeAll += wt;
		sumServTimeAll += st;
		minWaitTimeAll = (minWaitTimeAll < wt) ? minWaitTimeAll : wt;
		maxWaitTimeAll = (maxWaitTimeAll < wt) ? wt : maxWaitTimeAll;
		minServTimeAll = (minServTimeAll < st) ? minServTimeAll : st;
		maxServTimeAll = (maxServTimeAll < st) ? st : maxServTimeAll;
	}

	printf("For all simulation; "
		"avg/min/max wait time: %d/%d/%d; "
		"avg/min/max service time: %d/%d/%d "
		"max waiting queue size: %d\n",
		sumWaitTimeAll / Customers.NumInList(), minWaitTimeAll, maxWaitTimeAll,
		sumServTimeAll / Customers.NumInList(), minServTimeAll, maxServTimeAll,
		maxWaitingQueueAll);
}
