/* 
 * File:   SuperMarket.cc
 * Author: amin
 * 
 * Created on September 6, 2019, 4:32 PM
 */

#include "SuperMarket.h"
#include "Cashier.h"
#include "Customer.h"

int SuperMarket::peakHours[3];

SuperMarket::SuperMarket()
{
	//set peak hours
	peakHours[0] = 4;
	peakHours[1] = 5;
	peakHours[2] = 6;
	Cashier::lastId = 0;
	Customer::lastId = 0;
	//create min number of cashiers
	int i;
	for (i = 0; i < maxCashiers; i++) {
		Cashier* newCashier = new Cashier;
		Cashier::lastId++;
		printf("creating new cashier with id %d\n", newCashier->getId());
		if (i < minCashiers) {
			newCashier->open();
			printf("opening cashier %d\n", newCashier->getId());
		}
		cashiers.Append(newCashier);
	}
}

/*SuperMarket::SuperMarket(const SuperMarket& orig)
{
}*/

SuperMarket::~SuperMarket()
{
}

void SuperMarket::addCustomer(Customer *cust)
{
	customers.Append(cust);
	ListIterator<Cashier*> iterator(&cashiers);

	bool custAssigned = false;

	//printf("Adding customer %d to supermarket\n", cust->getId());

	for (; !iterator.IsDone(); iterator.Next()) {
		if (!custAssigned && iterator.Item()->isOpen() && iterator.Item()->hasRoom()) {
			iterator.Item()->addCustomer(cust);
			custAssigned = true;
			//printf("Assigning customer %d to cashier %d.\n", cust->getId(), iterator.Item()->getId());
		}
	}
	if (!custAssigned) {
		printf("Adding customer %d to waiting queue\n", cust->getId());
		waitingQueue.Append(cust);
		if (waitingQueue.NumInList() >= 10) {
			//open new cashier move 5 people to it from front of line then add this one to waiting queue
			printf("Waiting queue has %d customers. Opening new cashier. We currently have %d open cashiers.\n", waitingQueue.NumInList(), getNumOfOpenCashiers());
			if (maxCashiers > getNumOfOpenCashiers()) {

				ListIterator<Cashier*> iterator(&cashiers);

				for (; !iterator.IsDone(); iterator.Next()) {
					if (!iterator.Item()->isOpen()) {
						iterator.Item()->open();
						printf("New cashier id is %d and its num in line is %d\n", iterator.Item()->getId(), iterator.Item()->getNumInLine());
						//get 5 customers from waiting queue add to this cashier
						int i;
						for (i = 0; i < 5; i++) {

							iterator.Item()->addCustomer(waitingQueue.RemoveFront());

							//newCashier->getId();
						}
						break;
					}
				}


			} else
				printf("We can't open new cashier. We already have 10.\n");

		}
	}
}

Cashier* SuperMarket::openNewCashier()
{
	ListIterator<Cashier*> iterator(&cashiers);

	for (; !iterator.IsDone(); iterator.Next()) {
		if (!iterator.Item()->isOpen()) {
			iterator.Item()->open();
			return iterator.Item();
		}
	}

}

bool SuperMarket::isPeakHour(int hour)
{
	int i;
	for (i = 0; i < 3; i++)
		if (peakHours[i] == hour)
			return true;
	return false;
}

int SuperMarket::getNumOfOpenCashiers()
{
	ListIterator<Cashier*> iterator(&cashiers);

	int count = 0;

	for (; !iterator.IsDone(); iterator.Next()) {
		if (iterator.Item()->isOpen()) {
			count++;
		}
	}

	return count;
}

void SuperMarket::run()
{
	ListIterator<Cashier*> iterator(&cashiers);

	for (; !iterator.IsDone(); iterator.Next()) {
		iterator.Item()->run();
	}
	//now check if any cashier has room to accept new customer from waiting queue
	if (waitingQueue.NumInList() != 0) {
		ListIterator<Cashier*> iterator(&cashiers);

		for (; !iterator.IsDone(); iterator.Next()) {
			if (iterator.Item()->isOpen() && iterator.Item()->hasRoom() && waitingQueue.NumInList() != 0) {
				printf("Moving customer %d from waiting queue to cashier %d\n", waitingQueue.Front()->getId(), iterator.Item()->getId());
				iterator.Item()->addCustomer(waitingQueue.RemoveFront());
			}
		}
	}

	//close idle cashiers
	int numOpen = 0;
	if (waitingQueue.NumInList() == 0) {
		ListIterator<Cashier*> iterator(&cashiers);

		for (; !iterator.IsDone(); iterator.Next()) {
			if (iterator.Item()->isOpen())
				numOpen++;
			if (numOpen > minCashiers) {
				if (iterator.Item()->isOpen() && iterator.Item()->isEmpty()) {
					printf("Closing idle cashier %d\n", iterator.Item()->getId());
					iterator.Item()->close();
				}
			}
		}
	}

	//add one second to the waiting time of all customers who have processingTime=0
	ListIterator<Customer*> iteratorCust(&customers);
	for (; !iteratorCust.IsDone(); iteratorCust.Next()) {
		if (iteratorCust.Item()->getTimeProcessed() == 0)
			iteratorCust.Item()->incrementWaitTime();
	}
}

int SuperMarket::getWaitingQueueSize()
{
	return waitingQueue.NumInList();
}

int* SuperMarket::getCashiersStats()
{
	static int t[10];
	ListIterator<Cashier*> iterator(&cashiers);

	int i = 0;
	for (; !iterator.IsDone(); iterator.Next()) {
		t[i] = iterator.Item()->getMoreThan3Time();
		iterator.Item()->resetMoreThan3Time();
		i++;
	}

	return t;
}
