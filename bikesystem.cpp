#include "bikesystem.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

void bikesystem::addbike()
{
	bikes.push_back(createbike());

}

bool bikesystem::bikeIDexist(int number)
{
	for (auto bike : bikes) {
		if (bike->getbikeID() == number) {
			return true;
		}
	}
	return false;
}

bike* bikesystem::createbike()
{
	string brand;
	string model;
	int bikeID;
	string type;
	string framesize;
	double hourlyrate;

	// i still should add the exception handling 
	do {
		cout << " Enter a unique bikeNUM" << endl;
		if (!(cin >> bikeID)) {
			cin.clear(); // Clear error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard wrong input
			cout << "Invalid input. Please a valid ID consist of only numbers.\n";
			continue;
		}
		if (bikeIDexist(bikeID)) {
			cout << "This bike number already exists. Please enter a unique number." << endl;
		}
	} while (bikeIDexist(bikeID));

	cout << "Enter the brand" << endl;
	cin.ignore();
	getline(cin, brand);
	cout << "Enter the model" << endl;
	getline(cin, model);
	cout << "Enter the type " << endl;
	getline(cin, type);
	cout << "Enter the framesize" << endl;
	getline(cin, framesize);
	cout << " *** price ***" << endl;
	if (type == "electrical") {
		hourlyrate = 3.0;
		cout << "Electrical bike rate set to $3/hour" << endl;
	}
	else {
		hourlyrate = 1.5;
		cout << "Regular bike rate set to $1.5/hour" << endl;
	}
	// now let's create a objet's pointer to store the new bike  (new bike ) 
	bike* newbike = new bike(brand, model, bikeID, type, framesize, hourlyrate);// here we have called the constructor 
	return newbike;// returning the address of this object 
}



void bikesystem::displaybikes()const
{
	cout << "=============================================\n";
	cout << "           CURRENT BIKES INVENTORY                    \n";
	cout << "=============================================\n\n";

	if (bikes.empty()) {
		cout << " Error : There are no bikes on the system " << endl;
		return;
	}
	cout << left
		<< setw(5) << "NO."      // For the numbering
		<< setw(15) << "BRAND"
		<< setw(12) << "MODEL"
		<< setw(8) << "ID"
		<< setw(14) << "TYPE"
		<< setw(8) << "SIZE"
		<< setw(10) << "PRICE"
		<< setw(10) << "KM"
		<< setw(12) << "AVAILABILITY"
		<< endl;
	cout << "----------------------------------------------------------------------------------------" << endl;
	int num = 1; // will represent the number of the bike
	for (auto bike : bikes) {
		cout << setw(5) << num++  // prefix 
			<< setw(15) << bike->getbrand()
			<< setw(12) << bike->getmodel()
			<< setw(8) << bike->getbikeID()
			<< setw(14) << bike->gettype()
			<< setw(10) << bike->getsize()
			<< setw(10) << fixed << setprecision(2) << bike->priceof_Renting()
			<< setw(10) << bike->getmileage()
			<< setw(10) << (bike->getavailability() ? "Available" : "Rented     ")
			<< endl;
	}
	cout << "========================================================================================\n";

	int count = count_if(bikes.begin(), bikes.end(), [](const bike* bike) { return bike->getavailability(); });  // here i used lamada function instead of decaling an isolated function

	cout << "Total bikes: " << bikes.size() << " -> " << count << " available" << endl;
	system("pause"); // this will pause the system before going to the next thing 
}

void bikesystem::printbikedeatails(const bike* a)const
{
	cout << "Brand : " << a->getbrand() << "\n"
		<< "Model : " << a->getmodel() << "\n"
		<< " ID   : " << a->getbikeID() << "\n"
		<< "Type  : " << a->gettype() << "\n"
		<< "Size  : " << a->getsize() << "\n"
		<< "Price : " << fixed << setprecision(2) << a->priceof_Renting() << "\n"
		<< "mileage : " << a->getmileage() << "\n"
		<< "availability : " << (a->getavailability() ? "Available" : "Rented     \n")
		<< endl;
}

bike* bikesystem::findbikebyID(const int ID)const
{
	for (const auto bike : bikes) { // here the pointer is constant = bike*const bike  ( constant pointer to an object ) 
		if (bike->getbikeID() == ID) {
			return bike;  // returning a pointer 
		}
	}
	return nullptr;
}

bool bikesystem::showavaiablebikes() const
{
	if (bikes.empty()) {
		cout << " Error : There are no bikes on the system " << endl;
		return false;
	}
	cout << left << setw(12) << "BRAND" << setw(12) << "MODEL" << setw(8) << "ID" << setw(14) << "TYPE" << setw(8) << "SIZE" << setw(10) << "PRICE" << setw(10) << "KM" << setw(12) << "AVAILABILITY" << endl;
	for (auto bike : bikes) {
		if (bike->getavailability()) {
			cout << setw(12) << bike->getbrand() << setw(12) << bike->getmodel() << setw(8) << bike->getbikeID()
				<< setw(14) << bike->gettype() << setw(10) << bike->getsize() << setw(10) << fixed << setprecision(2) << bike->priceof_Renting()
				<< setw(10) << bike->getmileage() << setw(10) << (bike->getavailability() ? "Available" : "Rented     ") << endl;
		}
	}
	return true;
}


bool bikesystem::rentingbike(const int ID, const int userID)
{
	bike* biketorent = findbikebyID(ID);
	// checking if the bike exist or not
	if (!biketorent) {
		cout << "Error: Bike " << ID << " not found on our system!\n";
		return false;
	}
	// checking for availabilty for renting
	if (!biketorent->getavailability()) {
		cout << "the bike of ID " << biketorent->getbikeID() << " is already rented " << endl;
		return false;
	}

	// renting the bike 
	biketorent->startrenting();
	cout << " (: bike of ID " << ID << " is rented sucessfully :) !! Time is Running \n";
	customerBIKE[userID] = ID;
	return true;
}

void bikesystem::returningbike(const int ID, const int userID)
{

	bike* biketoreturn = findbikebyID(ID);
	if (!biketoreturn) {
		cout << "Error: Bike " << ID << " not found on our system!\n";
		return;
	}
	auto it = customerBIKE.find(ID);
	if (it != customerBIKE.end()) {
		customerBIKE.erase(it);
	}
	// checking for availabilty for returning
	if (biketoreturn->getavailability()) {
		cout << "Error : bike of ID " << ID << " was not rented " << endl;
		return;
	}
	// returning the bike 
	double period = biketoreturn->getprevioustime() + biketoreturn->getduration() + biketoreturn->getofflineperiod();
	//double offline_period = biketoreturn->getreopentime() - biketoreturn->getshutdowntime();
	biketoreturn->setreturning();
	biketoreturn->resetrentedstate();
	double cost = period * biketoreturn->priceof_Renting();
	cout << " Rental Duration: " << period << " seconds\n";
	cout << " Total Cost :  " << cost << " HUF" << "\n";
	cout << " Bike returned successfully!\n";

}

void bikesystem::deletingbike(const int ID)
{// add here to not delete any rented bikes , only the available ones 
	auto iterator = find_if(bikes.begin(), bikes.end(), [ID](const bike* b) { return b->getbikeID() == ID;});  // using stl and lamada instead of calling the function getbikebyID

	if (!(iterator == bikes.end())) {
		delete* iterator;  // it will delete the pointer which the iterator is pointing to 
		bikes.erase(iterator);
		cout << "Bike " << ID << " is deleted successfully.\n";
	}
	else {
		cout << "Error : Bike of ID " << ID << " is not found\n";
	}
}
void bikesystem::searchingbyID(const int ID)const
{
	const bike* biketodisplay = findbikebyID(ID);
	if (!biketodisplay) {
		cout << "Error : This Bike ID " << ID << " is not on the system\n";
		return;
	}
	printbikedeatails(biketodisplay);
}

void bikesystem::searchingbyBRAND(const string& b)const
{
	bool found = false;
	for (auto bike : bikes) {
		if (bike->getbrand() == b) {
			found = true;
			printbikedeatails(bike);
		}
	}
	if (!found) {
		cout << "NO Matching bikes for this brand : " << b << endl;
	}
}

void bikesystem::veiwingRentals()
{
	if (customerBIKE.empty()) {
		cout << "NO active rentals\n";
		return;
	}
	cout << "\n=== ACTIVE RENTALS ===\n";
	cout << "-------------------------\n";
	cout << left << setw(15) << "Customer ID"
		<< setw(10) << "Bike ID" << "\n";
	cout << "-------------------------\n";
	for (auto it = customerBIKE.begin(); it != customerBIKE.end(); ++it) {
		cout << setw(15) << it->first
			<< setw(10) << it->second
			<< "\n";
	}
}


void bikesystem::savingbike() const
{
	ofstream out_file("bikes_data.txt");
	if (out_file.is_open()) {

		for (auto bike : bikes) {

			out_file << bike->getbrand() << "," << bike->getmodel() << "," << bike->getbikeID() << "," << bike->gettype() << "," << bike->getsize() << ","
				<< bike->priceof_Renting() << "," << bike->getmileage() << "," << bike->getavailability() << ",";
			if (!bike->getavailability()) {
				bike->recordshutdowntime();
				bike->setprevioustime(bike->getprevioustime() + bike->getduration());
				out_file << bike->getprevioustime() << ","
					<< bike->getlastshutdowntime() << ","
					<< bike->getofflineperiod();

			}
			else {
				out_file << 0 << "," << 0 << "," << 0;
			}
			out_file << endl;

		}
		out_file.close();

	}
	else {
		cout << "Error : The file cannot be opened\n";
	}

}
// in the loadingbikes function , we will just copy the information of the bikes that are stoed in the file  
void bikesystem::loadingbikes()
{
	ifstream in_file("bikes_data.txt"); // Open the file for reading
	string brand, model, type, framesize;
	int bikeID;
	double hourlyrate, mileage;
	bool availabilty;
	double secnumber;
	time_t shutdowntime;
	double offlinesecs;
	string line;
	if (in_file.is_open()) {
		while (getline(in_file, line)) {  // it will stop reading when it sees a new line
			stringstream bikestream(line);
			getline(bikestream, brand, ',');
			getline(bikestream, model, ',');
			bikestream >> bikeID;
			bikestream.ignore();  // this will let us ignore the next thing and it will be the comma in our case (,) 
			getline(bikestream, type, ',');
			getline(bikestream, framesize, ',');
			bikestream >> hourlyrate;
			bikestream.ignore();
			bikestream >> mileage;
			bikestream.ignore();
			bikestream >> availabilty;
			bikestream.ignore();
			bikestream >> secnumber;      /// this will be get the previous time 
			bikestream.ignore();
			bikestream >> shutdowntime;
			bikestream.ignore();
			bikestream >> offlinesecs;
			bike* newbike = new bike(brand, model, bikeID, type, framesize, hourlyrate);
			newbike->setavailablty(availabilty);
			newbike->setnewmileage(mileage);

			if (!newbike->getavailability()) {

				newbike->setprevioustime(secnumber);
				auto now = steady_clock::now();
				newbike->rentTime = now;
				newbike->loading_time(shutdowntime);
				newbike->setofflineperiod(offlinesecs); // this will update the previous offlineperoid 
				newbike->recordrestarttime(); // this will get the restart time and then modify the offlineperoid by adding the previous one to the new one

			}
			else {
				newbike->setprevioustime(secnumber);
			}
			bikes.push_back(newbike);
		}
	}
	else {
		cout << "Error : The file cannot be opened\n";
	}
}

bool bikesystem::confirmexit()
{
	char answer;
	cout << "Are you sure u want to exit the program : (y/n) " << endl;
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {

		return true;
	}
	else if (answer == 'n' || answer == 'N') {
		return false;
	}
}

bikesystem::~bikesystem()
{
	cout << "cleaning memroy leaks" << endl;
	savingbike();
	for (bike* bike : bikes) { // here auot =  bike* 
		delete bike;  // freeing the allocated memory 
	}
	bikes.clear();  // cuz when we overload the bikes again , we must have been deleted the previous bikes
}


void lookingfor_Bike(const bikesystem& search) {  // passing by refrence in c++ style 
	string brand;
	int bikeID;
	cout << "1: search by ID  2:search by Brand\n\n";
	int choice;
	cout << "Enter your choice\n";
	while (!(cin >> choice) || choice < 1 || choice > 3) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input, Try again!\n";
	}
	switch (choice) {
	case 1:
		cout << "Enter bikeID\n";
		cin >> bikeID;
		search.searchingbyID(bikeID);
		break;
	case 2:
		cout << "Enter the Brand\n";
		cin.ignore();
		getline(cin, brand);
		search.searchingbyBRAND(brand);

	}
}