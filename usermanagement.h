#pragma once
#include "user.h"
class usermanagement {
private:
	vector <user*>users;
	bikesystem& system; // creating a reference to the bikesystem class to be able to call its functions in the user menu and also to link the users with the bikes they rented and that is why we need this reference

public:
	usermanagement(bikesystem& sys) :system(sys) {} // we must initialize the reference in the constructor and that is why we have this constructor
	customer* registercustomer(string name, string password, int ID);
	admin* registerAdmin(string name, string pass, int ID);
	user* login(string name, string password, int ID);
	void saveusers()const;
	void loadingusers();
	~usermanagement();
};

void handlemenu2();