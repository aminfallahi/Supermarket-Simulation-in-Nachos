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
SimpleThread(int which)
{
	int num;

	for (num = 0; num < 5; num++) {
		printf("*** thread %d looped %d times\n", which, num);
		//kernel->currentThread->Yield();
	}
}

void
ThreadTest()
{
	SuperMarket sm;
	srand(time(NULL));
	Customer::lastId = 0;
	char stats[10000];

	List<Customer*> Customers;


	int hour, minute, second, i, custNum, custSec;

	//FOR STATS
	int sumWaitTimeAll = 0, minWaitTimeAll = 10000, maxWaitTimeAll = 0,
		sumServTimeAll = 0, minServTimeAll = 10000, maxServTimeAll = 0,
		maxWaitingQueueAll = 0;

	for (hour = 2; hour < 7; hour++) {

		//FOR STATS
		//numCustInHourST holds the number of customers who have got service in each hour
		//numCustInHourWT holds the number of customers who have waited in store in each hour
		int sumCust = 0, numCustInHourST = 0, numCustInHourWT = 0,
			sumWaitTime = 0, minWaitTime = 10000, maxWaitTime = 0,
			sumServTime = 0, minServTime = 10000, maxServTime = 0,
			sumOpenLines = 0, maxOpenLines = 0,
			sumWaitingQueue = 0, minWaitingQueue = 10000, maxWaitingQueue = 0;

		for (minute = 0; minute < 60; minute++) {
			printf("----------\nTIME: %02d:%02d\n", hour, minute);
			if (sm.isPeakHour(hour))
				custNum = rand() % 6 + 5; //peak hours 5-10 customers per minute
			else
				custNum = rand() % 6; //reg hours 0-5 customers per minute
			if (custNum > 0)
				custSec = 60 / custNum;
			for (second = 0; second < 60; second++) {
				if (custNum != 0 and second % custSec == 0) {
					sumCust++;
					Customer* cust = new Customer; //create new customer
					Customers.Append(cust);
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
		ListIterator<Customer*> custIter(&Customers);
		for (; !custIter.IsDone(); custIter.Next()) {
			int wt = custIter.Item()->getHourlyWaitTime();
			int st = custIter.Item()->getHourlyTimeProcessed();
			if (wt != 0) {
				sumWaitTime += wt;
				numCustInHourWT++;
			}
			if (st != 0) {
				sumServTime += st;
				numCustInHourST++;
			}
			minWaitTime = (minWaitTime < wt) ? minWaitTime : wt;
			maxWaitTime = (maxWaitTime < wt) ? wt : maxWaitTime;
			minServTime = (minServTime < st) ? minServTime : st;
			maxServTime = (maxServTime < st) ? st : maxServTime;
			custIter.Item()->resetHourlyTimes();
		}
		sprintf(stats, "%s\n----------\nFROM 0%d:00:00 to 0%d:59:59:\n"
			"   average number of customers arriving for checkout (entered store): %d\n"
			"   average number of customers arriving for checkout (got service): %d\n"
			"   average/shortest/longest waiting time: %d / %d / %d\n"
			"   average/shortest/longest service time: %d / %d / %d\n"
			"   average number of open lines: %d\n"
			"   maximum number of open lines: %d\n"
			"   average/smallest/largest number of customers in the waiting queue: %d / %d / %d\n",
			stats, hour, hour, sumCust / 60, numCustInHourST / 60,
			sumWaitTime / numCustInHourWT / 60, minWaitTime / 60, maxWaitTime / 60,
			sumServTime / numCustInHourST / 60, minServTime / 60, maxServTime / 60,
			sumOpenLines / 60,
			maxOpenLines,
			sumWaitingQueue / 60, minWaitingQueue, maxWaitingQueue);

		int* moreThan3 = sm.getCashiersStats();
		sprintf(stats, "%s   average time each cashier will have more than 3 customers standing in line: \n", stats, hour);
		int i;
		for (i = 0; i < 10; i++) {
			sprintf(stats, "%s      cashier #%d %d\n", stats, i, moreThan3[i] / 60);
		}

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

	//because some customers will never be serviced, the wait time is high
	sprintf(stats, "%s\n**********\nFor all simulation;\n"
		"average/shortest/longest waiting time: %d/%d/%d;\n"
		"average/shortest/longest service time: %d/%d/%d\n"
		"maximum number of customers in the waiting queue at any time: %d\n",
		stats, sumWaitTimeAll / Customers.NumInList() / 60, minWaitTimeAll / 60, maxWaitTimeAll / 60,
		sumServTimeAll / Customers.NumInList() / 60, minServTimeAll / 60, maxServTimeAll / 60,
		maxWaitingQueueAll);

	printf(stats);

}
