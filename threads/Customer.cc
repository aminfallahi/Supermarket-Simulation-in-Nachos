/* 
 * File:   Customer.cc
 * Author: amin
 * 
 * Created on September 6, 2019, 4:32 PM
 */

#include "Customer.h"

int Customer::lastId;

Customer::Customer()
{
	id=lastId;
	lastId++;
	timeProcessed=0;
	waitTime=0;
	done=false;
}

/*Customer::Customer(const Customer& orig)
{
}*/

Customer::~Customer()
{
}

void Customer::setNumOfItems(int noi){
	this->numOfItems=noi;
}

int Customer::getNumOfItems(){
	return this->numOfItems;
}

bool operator==(const Customer &c1, const Customer &c2){
	return c1.id==c2.id;
}

void Customer::incrementTimeProcessed(){
	timeProcessed++;
}

int Customer::getTimeProcessed(){
	return timeProcessed;
}

int Customer::getId(){
	return id;
}

void Customer::incrementWaitTime()
{
	waitTime++;
}

void Customer::setDone()
{
	done=true;
}

int Customer::getWaitTime()
{
	return waitTime;
}
