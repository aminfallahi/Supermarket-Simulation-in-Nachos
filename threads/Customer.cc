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
	hourlyTimeProcessed=0;
	hourlyWaitTime=0;
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
	hourlyTimeProcessed++;
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
	hourlyWaitTime++;
}

void Customer::setDone()
{
	done=true;
}

int Customer::getWaitTime()
{
	return waitTime;
}

bool Customer::isDone()
{
	return done;
}

int Customer::getHourlyTimeProcessed()
{
	return hourlyTimeProcessed;
}

int Customer::getHourlyWaitTime()
{
	return hourlyWaitTime;
}

void Customer::resetHourlyTimes()
{
	hourlyTimeProcessed=0;
	hourlyWaitTime=0;
}
