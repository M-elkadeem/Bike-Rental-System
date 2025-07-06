#pragma once
#include "bike.h"
class bikesystem {
private:
	vector<bike*> bikes;   // creating dyanamic array of pointers  of the class bike
	map<int, int >customerBIKE;
public:
	void addbike();
	bool bikeIDexist(int number);
	bike* createbike();
	void displaybikes()const;
	void printbikedeatails(const bike* a)const;
	bike* findbikebyID(const int ID)const;
	bool showavaiablebikes()const;
	bool rentingbike(const int ID, const int userID = 0);
	void returningbike(const int ID, const int userID = 0);

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