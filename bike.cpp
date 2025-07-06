#include "bike.h"
using namespace std::chrono;
int bike::count = 0;

bike::bike(string br, string mod, int NUM, string ty, string size, double cost) :brand(br), model(mod), bikeID(NUM), type(ty), framesize(size)
, isavailable(true), rate_persec(cost), mileage(0.0) {
	count++; // increasing the number of bikes whenver we add a new one 
}

void bike::setprevioustime(double seconds)
{

	previoustime = seconds;// this will store the number of seconds of the duration before i exit the program

}

double bike::getprevioustime()
{
	return previoustime;
}

void bike::recordshutdowntime()
{
	auto now = system_clock::now();
	lastshutdowntime = system_clock::to_time_t(now);// this will convert the time (now) to seconds 
}

time_t bike::getlastshutdowntime()const
{
	return lastshutdowntime;
}

void bike::recordrestarttime()
{
	auto now = system_clock::now();
	programrestarttime = system_clock::to_time_t(now);
	if (lastshutdowntime > 0) {
		offlineperiod += difftime(programrestarttime, lastshutdowntime);
	}
}


void bike::loading_time(time_t shutdown_t)
{
	lastshutdowntime = shutdown_t;
}

void bike::setofflineperiod(double seconds)
{
	offlineperiod = seconds;
}

double bike::getofflineperiod()const
{
	return offlineperiod;
}

void bike::setavailablty(bool status)
{
	isavailable = status;
}

void bike::setnewmileage(double km)
{
	mileage += km;
}

string bike::getbrand() const
{
	return brand;
}

string bike::getmodel() const
{
	return model;
}

int bike::getbikeID() const
{
	return bikeID;
}

string bike::gettype() const
{
	return type;
}

string bike::getsize() const
{
	return framesize;
}

bool bike::getavailability() const
{
	return isavailable;
}

double bike::priceof_Renting() const
{
	return rate_persec;

}

double bike::getmileage() const
{
	return mileage;
}

void bike::startrenting()
{
	rentTime = steady_clock::now();
	setrented();
}

double bike::getduration()
{

	auto end = steady_clock::now();
	auto duration = duration_cast<seconds>(end - rentTime);
	return duration.count();// this will return the number of seconds in this duration
}

void bike::setrented()
{
	isavailable = false;
}

void bike::setreturning()
{
	isavailable = true;
}

void bike::resetrentedstate()
{
	previoustime = 0;
	offlineperiod = 0;
	lastshutdowntime = 0;
	programrestarttime = 0;
}

int bike::getTotalBikes()
{
	return count;
}