#pragma once
#include "user.h"
class usermanagement {
private:
	vector <user*>users;

public:
	customer* registercustomer(string name, string password, int ID);
	admin* registerAdmin(string name, string pass, int ID);
	user* login(string name, string password, int ID);
	void saveusers()const;
	void loadingusers();
	~usermanagement();
};

void handlemenu2();