#include "usermanagement.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

customer* usermanagement::registercustomer(string name, string password, int ID)
{
	for (auto u : users) {
		if (u->getuserID() == ID) {
			return nullptr;
		}
	}
	customer* newcustomer = new customer(name, password, ID);
	users.push_back(newcustomer);
	return newcustomer;
}

admin* usermanagement::registerAdmin(string name, string pass, int ID)
{
	admin* newadmin = new admin(name, pass, ID);
	users.push_back(newadmin);
	return newadmin;
}

user* usermanagement::login(string name, string password, int ID)
{
	for (auto u : users) {
		if (u->getuserID() == ID && u->checkpassword(password) && u->checkname(name)) {
			return  u; // this will return  admin object or customer object depending on the data 
		}
	}
	return nullptr;
}

void usermanagement::saveusers() const
{
	ofstream out_file("users_data.txt");
	if (out_file.is_open()) {
		for (auto user : users) {
			if (user->isadmin())
				continue;
			out_file << user->getname() << "," << user->getpassword() << "," << user->getuserID() << "," << "customer" << ",";
			vector <int>rentedbikesID = user->getrentedbikesID();
			for (auto ID : rentedbikesID) {
				out_file << ID << ",";
			}
			out_file << endl;
		}

		out_file.close();
	}
	else {
		cout << "Error: the file cannot be opened";
	}
}

void usermanagement::loadingusers()
{
	ifstream in_file("users_data.txt");
	string name, password, type;
	int userID, bikeID;
	string line;
	//customer* newcustomer;
	if (in_file.is_open()) {
		while (getline(in_file, line)) {  /// it will keep loading till it finds a new line and go to the next line and so on tell we finsih all the lines
			stringstream userstream(line);
			getline(userstream, name, ',');
			getline(userstream, password, ',');
			userstream >> userID;
			userstream.ignore(); // will ignore the , 
			getline(userstream, type, ',');

			if (type == "customer") {
				customer* newcustomer = registercustomer(name, password, userID);

				while (userstream >> bikeID) {
					newcustomer->addrental(bikeID);// to load the bikes and then link them with the customer 
					userstream.ignore();
				}
			}
		}
		in_file.close();
	}
	else {
		cout << "the file cannot be opened\n";
	}

}

usermanagement::~usermanagement()
{
	cout << "good bye";
	saveusers();
	for (auto user : users) {
		delete user;
	}
	users.clear();

}


// the following are the main menues 
void showusermenu() {
	system("cls");
	cout << "\n===== BIKE RENTAL SYSTEM =====\n"
		<< "1. Login\n"
		<< "2. Register as Customer\n"
		<< "3. Exit\n";

}
enum menuoptions2  { login = 1, Registering, Exiting };
underlying_type_t<menuoptions2>inputchoice;//to connect betweent the  inputchoice and the enumaration and i have forced that the variable inputchoice to be a numberation value only 
// and the reason for foceing  , is only let the user to enter what is in the enumeration not any integer value 
//menuoptions2 inputchoice;
void handlemenu2() {
	usermanagement manger;
	bikesystem object;
	object.loadingbikes();
	manger.loadingusers();
	manger.registerAdmin("mahmoud", "medo", 562005);
	showusermenu();
	while (true) {
		string username, password;
		int userID;
		cout << "Enter the choice you want " << endl;
		while (!(cin >> inputchoice) || inputchoice < 1 || inputchoice > 3) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, Try again!\n";
		}
		switch (inputchoice) {
		case login:
		{
			system("cls");
			cout << "Username : ";
			cin >> username;
			cout << "password : ";
			cin >> password;
			cout << "Your ID : ";
			cin >> userID;

			user* userobj = manger.login(username, password, userID);

			if (userobj) {
				cout << "loging is successful\n";
				// here i will add admin and the customer menu 
				userobj->showmenu(object);
			}
			else {
				cout << "Invalid data\n";
				system("pause");
			}
			break;
		}
		case Registering:
		{
			system("cls");
			cout << "Enter a unique username : ";
			cin >> username;
			cout << "Enter a password: ";
			cin >> password;
			cout << "Enter an ID: ";
			cin >> userID;
			user* newcustomer = manger.registercustomer(username, password, userID);
			if (newcustomer) {
				cout << "Registration is successful\n";
			}
			else {
				cout << "UserID already exists\n";
			}
			system("pause");
			break;
		}
		case Exiting:
			cout << "=== EXITING ===\n";
			if (object.confirmexit())
				return;
			break;
		}
		showusermenu();
	}
}
