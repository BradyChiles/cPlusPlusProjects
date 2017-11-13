/*
Marcus Murillo, Brady Chiles, Matthew Hayes
**************
This program was created for a POS (point of sale) system for a restruant to use. It can be used by the servers to show the menu and select each indiviudals order from
the menu displayed. It can then calculate the total bill for the table. It also has a function to print out daily totals. This function will add up all the of tables
orders for the day and give the user a total. The final function is a manager tool to calculate the number of staff needed based on the total bill as well as
calculate food cost, labor cost, and overhead. Additional comments have been included to explain the code further throughout the program.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

//Structs
struct Item{
	string name;
	double price;
	};

//Function Prototypes
void mainMenu();
void selection(int selection);
void menuSelection();
vector<Item> getMenu();
void printMenu(vector<Item> menu);
void printBill(vector<Item> totals);
void printDailyTotal();
void managerTools();

double dailyTotal = 0;

//Main function
int main() {
	
	mainMenu();
	
	return 0;
}

//Prints the main menu to the console for the user
void mainMenu() {
	int choice = 0;
	cout << "------------------------------" << endl;
	cout << "Please select which option you would like to choose" << endl << endl;
	cout << "1. Menu Selection" << endl;
	cout << "2. Daily Total" << endl;
	cout << "3. Manager Tools" << endl;
	cout << "4. Exit" << endl << endl;
	
	//if input is something other than an int
	if(!(cin >> choice)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a correct menu selection." << endl << endl;
		mainMenu();
	}else{
		selection(choice);
	}
		
}

//Will take the input of a selection and branch off from there
void selection(int selection){
	
	if(selection == 1) {
		menuSelection();			
	} else if(selection == 2) {
		printDailyTotal();
	} else if(selection == 3) {
		managerTools();
	}else if(selection == 4){
		cout << "Thank you, have a nice day!" << endl;
		exit(0);
	}else{
		cout << "That is not a valid selection!" << endl << endl;
		mainMenu();
	}
}

//Call for the menu to print and takes the user's input for menu items and stores it in a vector
void menuSelection(){
	int selection = 1;
	vector<Item> ticket;
	vector<Item> menu;
	
	menu = getMenu();
	printMenu(menu);
	
	while(selection != 0) {	
	
		cout << "Please select which menu item is to be added to the total" << endl;
		cout << "Enter 0 to print the bill" << endl;
		
		//If input is something other than an int
		while(!(cin >> selection)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Please enter a correct menu selection." << endl << endl;
		//If the user selects an item off the menu, it will be inserted into the totals vector
		}
		if(selection > 0 && selection <= menu.size()){
			ticket.push_back(menu[(selection - 1)]);
			cout << menu[(selection - 1)].name << " has been added to the menu" << endl << endl;
		//If the users enters 0, it will print the bill
		}else if(selection == 0){
			printBill(ticket);
		//If they enter somehting other than a menu selection or 0
		}else{
			cout << "Incorrect selection. Please enter 0 or a selection from the menu" << endl << endl;
		}
	}
}

//Reads the text files and populates the menu vector with menui items and prices
vector<Item> getMenu() {
	string iName;
	double iPrice;
	Item i;
	ifstream inFile;
	vector<Item> menu;
	
	inFile.open("Menu.txt");
	
	if (!inFile) {
    	cerr << "Unable to open file datafile.txt";
    	exit(1);   // call system to stop
	}
	
	while(inFile >> iName >> iPrice){
		i.name = iName;
		i.price = iPrice;
		
		menu.push_back(i);
	}
	
	inFile.close();
	
	return menu;
}

//Prints the menu to the console
void printMenu(vector<Item> menu){
	
	//Prints out the menu, separated by menu headers
	for(int x; x < menu.size(); x++) {
		if(x == 0){
			cout << endl;
			cout << "--------------------------------------" << endl;
			cout << "                Menu                  " << endl;
			cout << "--------------------------------------" << endl;
			cout << endl;
			cout << "Appetizers ---------------------------" << endl;
			cout << endl;
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}else if(x == 6){
			cout << endl;
			cout << "Soups and Salads ---------------------------" << endl;
			cout << endl;
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}else if(x == 15){
			cout << endl;
			cout << "Entrees ---------------------------" << endl;
			cout << endl;
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}else if(x ==22){
			cout << endl;
			cout << "Desserts ---------------------------" << endl;
			cout << endl;
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}else{
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}
	}
	cout << endl;
}

//Prints the bill, including items ordered, subtotal, tax, and total including tax
void printBill(vector<Item> ticket) {
	const double TAX_AMT = .06;
	double subTotal = 0;
	double tax = 0;
	double total = 0;
	
	cout << endl;
	cout << "----- Bill -----" << endl;
	cout << endl;
	
	for(int i = 0; i < ticket.size(); i++){
		cout << left << setw(22) << ticket[i].name << " $" << ticket[i].price << endl;
		subTotal += ticket[i].price;
	}
	
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
	
	cout << left << setw(22) << "Sub Total: " << " $" << subTotal << endl;
	
	tax = subTotal * TAX_AMT;
	cout << left << setw(22) << "Tax: " << " $" << tax << endl;
	
	total = subTotal + tax;
	cout << left << setw(22) << "Total: " << " $" << total << endl;
	
	cout << endl << endl;
	
	dailyTotal += subTotal;
	
	mainMenu();
}

//Print the total for the day
void printDailyTotal() {
	cout << endl << "------------------------------" << endl;
	cout << "Total for the Day is: $" << dailyTotal << endl << endl;
	mainMenu();
}

void managerTools(){
int selection = 3;
const double CUST_TO_TABLE = 60; // Average taken if 100 customer compacity > 20$ per customer on average > 3 Customers per table> where 60 comes from
int cooks;
int servers;
int managers;
const double M_PAY = 15.50; // Base Pay For All Managers
const double C_PAY = 10.10; // Base Pay For All Cooks
const double S_PAY = 8.20; //Base Pay For All Servers
double labor;
double hoursWorked = 7; // Base Hours Worked 4 to 11 can be changed to calculate weekly > Monthly if weekly/ Monthly Totals are available;
double foodCost;
double foodCostPercent = .60; // Assumed Average Margin of 60% for Food Cost;
double rent = 1500;
double totalCosts;
double rentTimePeriod = 30; // Rent is due every 30 days
double rentPerDay = rent / rentTimePeriod; // Calcs rent needed for each day to hit total Rent needed over time period
double tableAvg = dailyTotal / CUST_TO_TABLE;

	if (tableAvg <= 48) { // 48 per night is Minimum Tables Needed to Break Even With Minimum Labor Needed
		cooks = 2; // Minimum Cooks Needed
		servers = 3; // Minimum Servers Needed
		managers = 1; // Minimum Managers Needed
		
		labor = ((cooks * C_PAY * hoursWorked)+(servers * S_PAY * hoursWorked)+(managers * M_PAY * hoursWorked));
	}
	if (tableAvg <= 68 && tableAvg > 48) { // Need an Extra Cook
		cooks = 3;
		servers = 4;
		managers = 1;
		
		labor = ((cooks * C_PAY * hoursWorked)+(servers * S_PAY * hoursWorked)+(managers * M_PAY * hoursWorked));
	}
	if (tableAvg <= 120 && tableAvg > 68) { // Need Extra cook and server and Manager
		cooks = 4;
		servers = 5;
		managers = 2;
		
		labor = ((cooks * C_PAY * hoursWorked)+(servers * S_PAY * hoursWorked)+(managers * M_PAY * hoursWorked));
	}
	if (tableAvg <= 144 && tableAvg > 120) { // Need Extra cook and server
		cooks = 5;
		servers = 6;
		managers = 2;
		
		labor = ((cooks * C_PAY * hoursWorked)+(servers * S_PAY * hoursWorked)+(managers * M_PAY * hoursWorked));
	}
	if (tableAvg <= 168 && tableAvg > 144) { // Need Extra server
		cooks = 5;
		servers = 7;
		managers = 2;
		
		labor = ((cooks * C_PAY * hoursWorked)+(servers * S_PAY * hoursWorked)+(managers * M_PAY * hoursWorked));
	}
	if (tableAvg <= 192 && tableAvg > 168) { // Need Extra cook and server
		cooks = 6;
		servers = 8;
		managers = 2;
		
		labor = ((cooks * C_PAY * hoursWorked)+(servers * S_PAY * hoursWorked)+(managers * M_PAY * hoursWorked));
	}
		if (tableAvg > 192 && tableAvg <= 250) { // Need Extra cook and server 204 is Max tables on average but just incase i made it extra
		cooks = 6;
		servers = 8;
		managers = 2;
		
		labor = ((cooks * C_PAY * hoursWorked)+(servers * S_PAY * hoursWorked)+(managers * M_PAY * hoursWorked));
	}

	foodCost = dailyTotal * foodCostPercent;
	totalCosts = foodCost + labor + rentPerDay;
	double dailyOverhead = dailyTotal - totalCosts;
	cout << endl;
	cout << endl;
	cout << "    Total Labor Needed" << endl;
	cout << "   Number of Cooks Needed: " << cooks << endl;
	cout << " Number of Servers Needed: " << servers << endl;
	cout << "Number of Managers Needed: " << managers << endl;
	cout << endl;
	cout << endl;
	cout << "    Food Cost" << endl;
	cout << "Nightly Food Cost: " << foodCost << "$" << endl;
	cout << endl;
	cout << endl;
	cout << "    Labor Cost" << endl;
	cout << "Nightly Labor Cost: " << labor << "$" << endl;
	cout << endl;
	cout << endl;
	cout << "    Overhead" << endl;
	cout << "Nightly Overhead: " << dailyOverhead <<"$" << endl;
	cout << endl;
	cout << endl;
	
	mainMenu();
}





