/* 
 * File:   Cashier.cc
 * Author: amin
 * 
 * Created on September 6, 2019, 4:32 PM
 */


#include "Cashier.h"

int Cashier::lastId;

Cashier::Cashier()
{
	id=lastId;
	numInLine=0;
	status=false;
	printf("NEW CASHIER with id %d lastId %d\n",id,lastId);
	//lastId++;
}

/*Cashier::Cashier(const Cashier& orig)
{
}*/

Cashier::~Cashier()
{
}


void Cashier::open(){
	status=true;
}

void Cashier::close(){
	status=false;
}

bool Cashier::isOpen()
{
	return this->status;
}

bool Cashier::hasRoom(){
	//printf("hasRoom: cashier %d has %d customers in line\n",id,numInLine);
	if (numInLine<maxCustomers)
		return true;
	return false;
}

void Cashier::run(){
	//get front of the line
	if (numInLine>0){
		Customer *cust=line.Front();
		cust->incrementTimeProcessed();
		//printf("Customer %d has waited in line for %d seconds but his processing time is %d seconds\n",cust->getId(),cust->getTimeProcessed(),cust->getNumOfItems()*scanTime+startUpTime+closeTime);
		if (cust->getTimeProcessed()==cust->getNumOfItems()*scanTime+startUpTime+closeTime){
			//this customer is done
			printf("Customer %d is done.\n",cust->getId());
			cust->setDone();
			line.RemoveFront();
			numInLine--;
		}

	}
	
}

bool Cashier::isEmpty()
{
	if (line.NumInList()==0)
		return true;
	return false;
}

bool operator==(const Cashier &c1, const Cashier &c2){
	return c1.id==c2.id;
}

void Cashier::addCustomer(Customer *cust){
	line.Append(cust);
	numInLine++;
	printf("Cashier: Adding customer %d to cashier %d line. Now it has %d customers\n",cust->getId(),id,numInLine);
}

int Cashier::getId(){
	return id;
}

int Cashier::getNumInLine(){
	return numInLine;
}
