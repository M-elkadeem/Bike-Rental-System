#include <iostream>
#include "user.h"
using namespace std;

string user::getname()
{
	return name;
}

string user::getpassword()
{
	return password;
}

int user::getuserID()
{
	return userID;
}

bool user::checkname(string username)
{
	return name == username;
}

bool user::checkpassword(string pass)const
{
	return password == pass;
}

bool user::isadmin()
{
	return false;
}

user::~user()
{
}

void admin::showmenu(bikesystem& obj)
{
	enum adminoptions { display = 1, searching, add, deleting, viewing_Rentals, logingOut };  // the enumuration will improve the read ability 
	underlying_type_t<adminoptions>choice;
	while (true) {
		system("cls");
		cout << "\n=====ADMIN MENU======\n"
			<< "1: displaying Bikes\n"
			<< "2: searching\n"
			<< "3: adding bike\n"
			<< "4: deleting bike\n"
			<< "5: view All Rentals\n"
			<< "6: loging out\n";
		cout << "Enter choice: ";
		while (!(cin >> choice) || choice < 1 || choice > 6) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, Try again!\n";
		}
		switch (choice) {
		case display:
			system("cls");
			obj.displaybikes();
			break;
		case searching:
			system("cls");
			cout << "SEARCHING FOR A BIKE \n";
			lookingfor_Bike(obj);
			system("pause");
			break;
		case add:
			system("cls");
			cout << "=== ADDING BIKE ===\n";
			obj.addbike();
			//	object.savingbike();
			system("pause");
			break;
		case deleting:
			cout << "====== DELEEING BIKE ======\n";
			cout << "Enter the ID\n";
			int ID;
			cin >> ID;
			obj.deletingbike(ID);
			//	object.savingbike();
			system("pause");
			break;
		case viewing_Rentals:
			obj.veiwingRentals();
			system("pause");
			break;
		case logingOut:
			cout << "loging out.....\n";
			system("pause");
			return;
		}
	}
}

bool admin::isadmin()
{
	return true;
}
vector<int> admin::getrentedbikesID() const
{
	return {};
}
void customer::addrental(int bikeId)
{
	rentedbikesID.push_back(bikeId);
}

void customer::removeRental(int bikeID)
{
	auto it = find(rentedbikesID.begin(), rentedbikesID.end(), bikeID);
	if (it != rentedbikesID.end()) {
		rentedbikesID.erase(it);
	}
}

void customer::showmenu(bikesystem& object)
{
	enum custmoeroptions { renting = 1, returning, viewingmyBike, logingOut };  // the enumuration will improve the read ability 
	underlying_type_t<custmoeroptions>input;
	while (true) {
		cout << "\n===== CUSTOMER MENU =====\n"
			<< "1. Rent a Bike\n"
			<< "2. Return a Bike\n"
			<< "3. View my bike\n"
			<< "4. Logout\n";
		cout << "choose an operation\n";
		while (!(cin >> input)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, Try again!\n";
		}
		switch (input) {
		case renting:
			system("cls");
			cout << "=== RENTING  BIKE ===\n";
			cout << "\n Available Bikes\n";
			if (!object.showavaiablebikes()) {
				break;
			}
			int bikeID;
			cout << "\nEnter the bikeID to Rent : \n";
			cin >> bikeID;
			if (object.rentingbike(bikeID, userID)) {
				addrental(bikeID);
			}
			//object.savingbike();
			system("pause");
			break;
		case returning:
			system("cls");
			cout << "=== RETURNING BIKE ===\n";
			cout << "Enter the bikeID for Returning\n";
			cin >> bikeID;
			if (find(rentedbikesID.begin(), rentedbikesID.end(), bikeID) != rentedbikesID.end()) {
				object.returningbike(bikeID, userID);
				removeRental(bikeID);
				//object.savingbike();
			}
			else {
				cout << "YOU Didnot rent any bikes\n";

			}
			system("pause");
			break;
		case viewingmyBike:
			system("cls");
			if (rentedbikesID.empty()) {
				cout << "\nYou didn't rent any Bikes\n";
			}
			else {
				for (int ID : rentedbikesID) {
					object.searchingbyID(ID);
				}
			}
			system("pause");
			break;
		case logingOut:
			cout << "loging out....\n";
			return;
		}
	}

}

vector<int> customer::getrentedbikesID() const
{
	return rentedbikesID;
}