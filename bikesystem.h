#pragma once
#include "bike.h"
class bikesystem {
private:
	vector<bike*> bikes;   // creating dyanamic array of pointers  of the class bike
	map<int,vector <int>>customerBIKE; // this map will store the userID and the bikeID for each rental ( we can also use unordered_map but i prefer map for the sorting ) and it will only contain the rented bikes and their customers 


public:
	void addbike();
	bool bikeIDexist(int number);
	bool IsbikeRented(bike& Bike,int ID)const;
	bike* createbike();
	void displaybikes()const;
	void printbikedeatails(const bike* a)const;
	bike* findbikebyID(const int ID)const;
	bool showavaiablebikes()const;
	bool rentingbike(const int ID, const int userID = 0);
	void returningbike(const int ID, const int userID = 0);
	void setcustomerBIKE(int userID, int bikeID);

	void deletingbike(const int ID);
	void searchingbyID(const int ID)const;
	void searchingbyBRAND(const string& b)const;
	void veiwingRentals();

	void savingbike()const;
	void loadingbikes();
	bool confirmexit();
	~bikesystem();

};
void lookingfor_Bike(const bikesystem& search);