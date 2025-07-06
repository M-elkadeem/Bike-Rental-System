#pragma once
#include <string>
#include <vector>
#include <chrono>
#include<map>
#include "bikesystem.h"
using namespace std;
using namespace std::chrono;class user {
protected:
	string name;
	string password;
	int userID;
public:
	user(string n, string p, int ID) :name(n), password(p), userID(ID) {}

	string getname();
	string getpassword();
	int getuserID();
	bool checkname(string username);
	bool checkpassword(string pass)const;
	virtual void showmenu(bikesystem& system) = 0;
	virtual bool isadmin();
	virtual vector<int>  getrentedbikesID()const = 0;
	virtual ~user();
};

class admin :public user {
public:
	admin(string n, string pw, int ID) :user(n, pw, ID) {}
	void showmenu(bikesystem& obj)override;
	bool isadmin();
	vector<int>getrentedbikesID()const override;// it has to be written here as well or this class will be abstract and will cause many errors


};

class customer :public user {
private:
	vector <int> rentedbikesID;// this will only the store the bike's ID of the customer
public:
	customer(string n, string ps, int ID) :user(n, ps, ID) {}

	void addrental(int bikeId);
	void removeRental(int bikeID);
	void showmenu(bikesystem& obj)override;
	vector<int>getrentedbikesID()const override;// we made the return type vector cuz this what we are gonna return

};
