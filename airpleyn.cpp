#include <iostream>
#include <fstream> // input/output operations and file handling.
#include <sstream> // string stream processing.
#include <string> // string operations and manipulations
#include <cstdio> // standard input/output operations
#include <vector> // dynamic arrays
#include <iomanip> // Include the necessary header for setw
#include <stack> // stack data structure.
#include <windows.h> // clearing the console screen.
#include <thread> // multi-threading and time-related operations.
#include <cstdlib> // general purpose functions.
#include <chrono>


using namespace std;

struct Node {
    vector<string> row;
    Node* next;

    Node(const vector<string>& rowData) : row(rowData), next(nullptr) {}
};

stack<string> passengerStack;
vector<vector<string>> readCSV(const string& filename);
void display_flights(const string& filename);
void display_seats(const string& filename, const string& destination);
void passenger_info(const string& name, const string& flight_num, const string& seat, const string& cost, const int& idx);
int get_prices(string filename, string destination);
string find_cost(const string& selected_seat, const vector<vector<string>>& content, string destination);
string ask_name();
int find_flight_index(string filename, string destination);
void book_seat(const string& filename, const string& destination);
void print_receipt();
void checkFlights();
void Abt();
int choice;
void menu(string part);
void press_enter();
void printing();
void promo();
void signIn();
void signUp();
void logOut();
void delete_row(const string& filename, int row_index);
int name_indx(string filename, string name);
vector<string> seat_indx(string filename, string name);
void revert_seat(const string& filename, string name, int flight_idx, string seats, string flightnum);
int ask_promo(string destination);
int cancel_find_flight_index(string filename, string destination);


bool run_promo = false;

struct User {
    string username;
    string password;
};

User users[10];
int userCount = 0;

bool sign_in_flag = true;

bool flag = true;


int main()
{
    cout<<" _______    ______   __    __         ______   ______  _______   __        ______  __    __  ________   ______  "<<endl;
    cout<<R"( |       \  /      \ |  \  |  \       /      \ |      \|       \ |  \      |      \|  \  |  \|        \ /      \ )"<<endl;
    cout<<R"( | $$$$$$$\|  $$$$$$\| $$  | $$      |  $$$$$$\ \$$$$$$| $$$$$$$\| $$       \$$$$$$| $$\ | $$| $$$$$$$$|  $$$$$$\)"<<endl;
    cout<<R"( | $$__/ $$| $$___\$$| $$  | $$      | $$__| $$  | $$  | $$__| $$| $$        | $$  | $$$\| $$| $$__    | $$___\$$)"<<endl;
    cout<<R"( | $$    $$ \$$    \ | $$  | $$      | $$    $$  | $$  | $$    $$| $$        | $$  | $$$$\ $$| $$  \    \$$    \ )"<<endl;
    cout<<R"( | $$$$$$$\ _\$$$$$$\| $$  | $$      | $$$$$$$$  | $$  | $$$$$$$\| $$        | $$  | $$\$$ $$| $$$$$    _\$$$$$$\)"<<endl;
    cout<<R"( | $$__/ $$|  \__| $$| $$__/ $$      | $$  | $$ _| $$_ | $$  | $$| $$_____  _| $$_ | $$ \$$$$| $$_____ |  \__| $$)"<<endl;
    cout<<R"( | $$    $$ \$$    $$ \$$    $$      | $$  | $$|   $$ \| $$  | $$| $$     \|   $$ \| $$  \$$$| $$     \ \$$    $$)"<<endl;
    cout<<R"( \$$$$$$$   \$$$$$$   \$$$$$$        \$$   \$$ \$$$$$$ \$$   \$$ \$$$$$$$$ \$$$$$$ \$$   \$$ \$$$$$$$$  \$$$$$$ )"<<endl;
    printing();
    while (sign_in_flag)
    {
        menu("signin");
    }

    while (flag)
    {
        menu("not signin");
    }
    return 0;
}

void clearscreen()
{
    system("cls");
}

vector<vector<string>> readCSV(const string& filename)
{       /*The readCSV function reads a CSV file and parses its contents into a 2D vector,
         representing rows and columns of the data.*/

    vector<vector<string>> data; //stores in 2d array
    ifstream inputFile(filename);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile, line)) 
        {
            vector<string> row;
            stringstream ss(line); // stringstream to access each element of string
            string cell;

            while (getline(ss, cell, ','))
            {
                row.push_back(cell); // cell elements are placed in row
            }

            data.push_back(row);
        }

        inputFile.close();
    }
    else
    {
        cout << "UNABLE TO OPEN FILE: " << filename << endl;
    }

    return data;
}

void display_flights(const string& filename)
{   /* The display_flights function reads a CSV file specified by filename, extracts the contents using the readCSV function, 
    and displays the first three columns of each row in a formatted manner.*/

    vector<vector<string>> content = readCSV(filename);

    const int columnWidth = 25;

    for (const auto& row : content)
    {
        if (row.size() >= 3)
        {
            cout << left << setw(columnWidth) << row[0];
            cout << left << setw(columnWidth) << row[1];
            cout << left << setw(columnWidth) << row[2] << endl;
        }
    }
}

void display_seats(const string& filename, const string& destination) {
    /*The display_seats function reads a CSV file, searches for a destination, and displays the available seats in a formatted layout. 
    If the destination is not found, it provides an appropriate message.*/

    vector<vector<string>> content = readCSV(filename); // ;oads data

    int idx = -1; // destination index in availableflights.csv
    for (int i = 0; i < content.size(); i++) {
        if (content[i][1].find(destination) != string::npos) {
            idx = i;
            break;
        }
    }

    if (idx != -1) { // checks if idx is valid
        string& flight_number = content[idx][0];
        string& location = content[idx][1];
        string& available_seats = content[idx][2];

        // Print flight number and destination
        cout << "================================\n";
        cout << "Flight number: " << flight_number << endl;
        cout << "Destination: " << location << endl;
        cout << "================================\n";

        size_t start_index = 3;
        size_t num_rows = (content[idx].size() - start_index) / 8;

// Print the seats in the desired format
    for (size_t i = 0; i < num_rows; ++i) {
        cout<<"       ";
        for (size_t j = start_index + i * 8; j < (start_index + i * 8) + 4 && j < content[idx].size(); ++j) {
            if (j>34)
            {
                break;
            }
            else
            {
                if (j%2==1)
                {
                    cout<<content[idx][j];
                }
                else
                {
                cout << content[idx][j] << "   ";}}
        }
        if(i <4)
        {
        cout << "\n       ";}
        for (size_t j = start_index + i * 8 + 4; j < (start_index + i * 8) + 8 && j < content[idx].size(); ++j) {
            if (j>34)
            {
                break;
            }
            else{
            if (j%2==1)
                {
                    cout<<content[idx][j];
                }
                else
                {
            cout << content[idx][j] << "   ";}}
        }
        if(i <4)
        {
        cout << endl;}
}
        cout<<endl;

        start_index = 35;
        num_rows = (content[idx].size() - start_index + 2) / 9;

        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = start_index + i * 9; j < (start_index + i * 9) + 9 && j < content[idx].size(); ++j) {
                cout << content[idx][j];
                if ((j - start_index + 1) % 3 == 0) {
                    cout << "   ";
                }
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "Destination not found." << endl;
    }
}

void passenger_info(const string& name, const string& flight_num, const string& seat, const string& cost, const int& idx)
{   /*The passenger_info function saves passenger information in a file and pushes it onto a stack. It writes the information to a file named 
    "passengerflights.csv" and displays a success message if the operation is successful, otherwise an error message.*/

    // Store passenger information in the stack
    ofstream file("passengerflights.csv", ios::app); //opens the filename
    if (file.is_open())
    {
        file << name << "," << flight_num << "," << seat << "," << cost << "," << idx << "\n"; //writes in the filename
        cout << "PASSENGER INFORMATION SAVED SUCCESSFULLY!" << endl;
        file.close();
    }
    else
    {
        cout << "Error opening the file for writing." << endl;
    }

    string passengerData = name + "," + flight_num + "," + seat + "," + cost;
    passengerStack.push(passengerData); //pushes string into the stack
    cout << "PASSENGER INFORMATION SAVED SUCCESSFULLY!" << endl;
}

Node* linkedlist_readCSV(const string& filename) {
    /*The linkedlist_readCSV function reads a CSV file and creates a linked list of nodes to store the data. It returns the pointer to the head of the linked list.*/
    Node* head = nullptr;
    ifstream inputFile(filename);
    string line;

    if (inputFile.is_open()) {
        Node* current = nullptr;
        while (getline(inputFile, line)) {
            vector<string> rowData;
            stringstream ss(line);
            string cell;

            while (getline(ss, cell, ',')) {
                rowData.push_back(cell);
            }

            Node* newNode = new Node(rowData);
            if (head == nullptr) {
                head = newNode;
                current = head;
            } else {
                current->next = newNode;
                current = newNode;
            }
        }

        inputFile.close();
    } else {
        cout << "UNABLE TO OPEN FILE: " << filename << endl;
    }

    return head;
}

void deleteLinkedList(Node* head)
{   /*The deleteLinkedList function deletes a linked list by iterating through the nodes, starting from the given head node, 
    and freeing the memory occupied by each node using the delete operator.*/
    Node* current = head;
    while (current != nullptr)
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

int get_prices(string filename, string destination)
{   /*The get_prices function reads a CSV file using a linked list, searches for a specific destination, retrieves and converts the corresponding price
     to an integer, and returns it. Memory allocated for the linked list is freed using the deleteLinkedList function.*/
    string price;
    Node* head = linkedlist_readCSV(filename); //uses linkedlist when getting the content of the file

    Node* current = head;
    while (current != nullptr)
    {
        if (current->row[0].find(destination) != string::npos)
        {
            price = current->row[1];
            break;
        }
        current = current->next;
    }

    deleteLinkedList(head); // Assuming you have a function to delete the linked list and free memory

    int price_num;
    price_num = stoi(price);
    return price_num;
}

string find_cost(const string& selected_seat, const vector<vector<string>>& content, string destination)
{   /*The find_cost function calculates and returns the cost of a selected seat based on the destination and seat type. It retrieves the price from a 
    CSV file using the get_prices function and applies a luxury cost multiplier if the seat corresponds to the luxury section. The cost is returned as a string.*/

    char arr[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}; // stores the first letter of the seats in arrays
    char arr2[8] = {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'}; // economy seats
    const string FILENAME = "flightprices.csv";
    int price;
    string price_str;
    for (int i = 0; i < 8; i++)
    {
        if (selected_seat.find(arr[i]) != string::npos) //checks if selected_seat has the row in the given array
        {
            price = get_prices(FILENAME, destination);
            int luxury_cost = price + (price * 0.4);
            price_str = to_string(luxury_cost);
            return price_str;
        }
        else if (selected_seat.find(arr2[i]) != string::npos) // same with the above if
        {
            price = get_prices(FILENAME, destination);
            price_str = to_string(price);
            return price_str;
        }
    }
    return "";
}

string ask_name()
{
    string name;
    cout << "Input the name of the ticket holder: ";
    cin >> name;
    return name;
}

int find_flight_index(string filename, string destination)
{   /*The find_flight_index function reads a CSV file, searches for a specific destination, and returns the corresponding flight index.
    It iterates through the data, compares the destination to the available flights, and returns the flight index (converted to an integer) if found. 
    If the destination is not found, it returns -1.*/

    vector<vector<string>> content = readCSV(filename); // reads data
    int idx; // idx holder
    for (int i = 1; i < content.size(); i++)
    {
        if (content[i][1].find(destination) != string::npos) // if destination from user is equal to the destination in the availableflights
        {
            idx = stoi(content[i][0]); // string to integer the flight number, set it to idx
            return idx;
        }
    }
    return -1;
}

void book_seat(const string& filename, const string& destination)
{   /*The book_seat function enables seat booking for a specified destination by interacting with a CSV file. 
    It reads the file, searches for the appropriate flight index, prompts the user to select a seat, updates seat availability, 
    gathers passenger information, calculates the ticket cost (with an optional promo), presents a booking confirmation, saves passenger details, 
    updates the CSV file, generates a receipt, and displays appropriate messages throughout the process.*/

    vector<vector<string>> content = readCSV(filename); //loads data

    int flight_index = find_flight_index(filename, destination); // gets the index of the flight based on destination
    int flightnum[16]; // stores the flight number of each flight
    for (int i = 1; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            if (j == 0)
            {
                flightnum[i - 1] = stoi(content[i][0]);
            }
        }
    }

    //binary search
    int idx = -1;
    int left = 0;
    int right = content.size() - 1;
    int counter = 0;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (flightnum[mid] == flight_index)
        {
            idx = mid;
            break;
        }
        else if (flightnum[mid] < flight_index)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
        counter++;
    }
    
    string selectedSeat, name, flightNum, cost;
    int seat_index = -1, choice;


    if (idx != -1)
    {
        clearscreen();
        display_seats(filename, destination);

        cout << "Select Desired Seat: ";
        cin >> selectedSeat;

        for (int i = 3; i < content[idx+1].size(); i++)
        {
            if (selectedSeat == content[idx+1][i] && content[idx+1][i] != "X ") //checks if selectedseats is equal to content and if it's not X
            {
                seat_index = i;
                int seatsNum = stoi(content[idx+1][2]) - 1; // subtracts one from available seats in flight
                content[idx+1][2] = to_string(seatsNum); //sets seatsNum to avaialableflights.csv
                content[idx+1][i] = "X "; // sets the selectedseat to X which signifies that it was already taken
                break;
            }
        }

        if (seat_index != -1)
        {
            name = ask_name(); // gets the name of ticket holder

            flightNum = content[idx+1][0];
            cost = find_cost(selectedSeat, content, destination);

            int price = 0;

                if (run_promo == false)
                {
                    clearscreen();
                    cout << "============= Confirmation of Booking ============\n";
					cout << "Name: " << name << endl;
					cout << "Flight Number: " << flightNum << endl;
					cout << "Destination: " << destination << endl;
					cout << "Selected Seat: " << selectedSeat << endl;
					cout << "Ticket Cost: " << cost << endl;
					cout << "==================================================\n";
                    press_enter();

                    passenger_info(name, flightNum, selectedSeat, cost, seat_index);
                }
                else if (run_promo == true)
                {
                    price = ask_promo(destination);
                    int cost_int = stoi(cost);
                    float computation = (1 - (price / 100.0)) * (cost_int); // computes for ticket cost
                    int computation_int = static_cast<int>(computation);
                    string computation_str = to_string(computation_int);
                    clearscreen();

                    cout << "============= Confirmation of Booking ============\n";
					cout << "Name: " << name << endl;
					cout << "Flight Number: " << flightNum << endl;
					cout << "Destination: " << destination << endl;
					cout << "Selected Seat: " << selectedSeat << endl;
					cout << "Ticket Cost: " << computation_str << endl;
					cout << "==================================================\n";
                    press_enter();

                    passenger_info(name, flightNum, selectedSeat, computation_str, seat_index);
                }
                else
                {
                    cout<< "========================= INVALID RUN PROMO =========================";
                    press_enter();
                }
                ofstream outputFile(filename);
                if (outputFile.is_open())
                {
                    for (const auto& row : content)
                    {
                        for (size_t i = 0; i < row.size(); i++)
                        {
                            outputFile << row[i];
                            if (i != row.size() - 1)
                            {
                                outputFile << ",";
                            }
                        }
                        outputFile << endl;
                    }

                    outputFile.close();
                    clearscreen();
                    printing();
                    print_receipt();
                    press_enter();
                    cout << "FILE MODFIED SUCCESSFULLY!" << endl;
                }
                else
                {
                    cout << "COULD NOT OPEN THE FILE FOR WRITING!" << endl;
                    menu("part2");
                }
        }
        else
        {
            cout << "INVALID SEAT SELECTION!" << endl;
        }
    }
    else
    {
        cout << "DESTINATION NOT FOUND!" << endl;
    }
}

void press_enter()
{ 
    cout << "\nKINDLY PRESS ENTER TO CONTINUE...";
    cin.ignore();
    cin.get();
}

void print_receipt()
{   /*The print_receipt function prints receipts for each passenger by retrieving the information from the passengerStack. 
It pops the top element of the stack, parses the passenger information, and displays the receipt containing the passenger's information*/
    if (passengerStack.empty())
    {
        cout << "NO PASSENGER INFORMATION AVAILBELE!" << endl;
        return;
    }

    while (!passengerStack.empty())
    {
        string passengerData = passengerStack.top();
        passengerStack.pop(); //removes top element of stack

        stringstream ss(passengerData);
        string item;
        vector<string> passengerInfo;

        while (getline(ss, item, ','))
        {
            passengerInfo.push_back(item);
        }

        if (passengerInfo.size() == 4)
        {
            string name = passengerInfo[0];
            string flightNum = passengerInfo[1];
            string seat = passengerInfo[2];
            string cost = passengerInfo[3];

			cout << "\n================= Receipt ================\n";
			cout << "Name: " << name << endl;
			cout << "Flight Number: " << flightNum << endl;
			cout << "Seat: " << seat << endl;
			cout << "Cost: " << cost << endl;
			cout << "==========================================\n";

        }
    }
}

void Abt(){
system("cls");
cout<<"  _|_|        _|_|_|          _|_|        _|    _|      _|_|_|_|_|  "<<endl;
cout<<"_|    _|      _|    _|      _|    _|      _|    _|          _|      "<<endl;
cout<<"_|_|_|_|      _|_|_|        _|    _|      _|    _|          _|      "<<endl;
cout<<"_|    _|      _|    _|      _|    _|      _|    _|          _|      "<<endl;
cout<<"_|    _|      _|_|_|          _|_|          _|_|            _|      "<<endl;                                
cout<<endl;
cout<<endl;                                
cout<<"+-------------------------------------------------------------------------------+"<<endl;
cout<<"| Introducing the high-flying C++ Flight Booking System! Buckle up and prepare  |"<<endl;
cout<<"| for an exciting journey through the world of aviation. With a smooth sign-in  |"<<endl;
cout<<"| and sign-up function, you'll have access to a sky full of possibilities. Book |"<<endl;
cout<<"| your dream destination effortlessly and cancel with ease if plans change. But |"<<endl;
cout<<"| wait, there's more! Our promo menu will sweep you off your feet with exclusive|"<<endl;
cout<<"| deals and discounts, making your travel experience even more unforgettable.   |"<<endl;
cout<<"| Soar through the code and enjoy the seamless interface as you navigate your   |"<<endl;
cout<<"| way to the perfect flight. Whether you're a jetsetter or a casual traveler,   |"<<endl;
cout<<"| this system will keep you flying high and craving more adventures. Bon voyage!|"<<endl;
cout<<"+-------------------------------------------------------------------------------+"<<endl;
cout<<endl;
cout<<endl;
cout<<"Project of:"<<endl;
cout<<"Marc Linus Rosales"<<endl;
cout<<"Kristhian Pinili"<<endl;
cout<<"Gerard Andrei Malapote"<<endl;
cout<<endl;
cout<<"This project is done in partial fulfillment of the final exams in Data Structures and Algorithms."<<endl;
cout<<endl;

    press_enter();
    clearscreen();        
}

void promo()
{
    clearscreen();
    string filename = "Promos.csv";
    vector<vector<string>> content = readCSV(filename); //loads content of file
    cout<<"=============Available Promos at Blank Airline=============\n";
    display_flights(filename);
    cout<<"===========================================================\n";
}

void menu(string part){
    clearscreen();
    int flightindex = 0;
    int rowToDelete = 0;
    if (part == "signin")
    {
        cout << "***************** Main Menu *****************\n";
        cout << "*   1. Sign In                              *\n";
        cout << "*   2. Sign Up                              *\n";
        cout << "*   3. Exit                                 *\n";
        cout << "*********************************************\n";
        cout << "Enter your choice: ";

        cin >> choice;

        clearscreen();

        switch (choice) {
            case 1:
                signIn();
                break;
            case 2:
                signUp();
                break;
            case 3:
                    cout << "+-----------------------------------------------------+\n";
    				cout << "| THANK YOU FOR USING BSU AIRLINES. HAVE A SAFE TRIP! |\n";
  					cout << "+-----------------------------------------------------+\n";
                sign_in_flag = false;
                flag = false;
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    }
    else
    {
    cout << "+----------------------------------------+\n";
    cout << "|        Welcome to BSU Airline          |\n";
    cout << "+----------------------------------------+\n";
    cout << "|                                        |\n";
    cout << "|       1. Check Available Flights       |\n";
    cout << "|       2. Book a Flight                 |\n";
    cout << "|       3. Cancel a Flight               |\n";
    cout << "|       4. Check Flight Promos           |\n";
    cout << "|       5. About                         |\n";
    cout << "|       6. Exit                          |\n";
    cout << "|                                        |\n";
    cout << "+----------------------------------------+\n";
	cout<<endl;
	cout<<"\nEnter Choice: ";
    int choice, price;
	cin>>choice;
	string destination, filename, name;
    vector<string> seat;
    vector<vector<string>> content;


	switch (choice){
		case 1:
            clearscreen();
            cout<<"=================Available Flights at Blank Airlines=================\n";
            display_flights("availableflights.csv");
            cout<<"=====================================================================\n";
            press_enter();
			break;
		case 2:
            run_promo = false;
            clearscreen();
            cout<<"=================Available Flights at Blank Airlines=================\n";
            display_flights("availableflights.csv");
            cout<<"=====================================================================\n";
            cout << "\nEnter Desired Destination: ";
            cin >> destination;

            book_seat("availableflights.csv", destination);

			break;
		case 3:
            clearscreen();
            filename = "passengerflights.csv";
            cout<<"====Cancellation of Flight====\n\n";
            cout<<"Name to be deleted: ";
            cin>>name;
            rowToDelete = name_indx("passengerflights.csv", name); // Example: delete the 3rd row
            seat = seat_indx("passengerflights.csv", name);
            flightindex = cancel_find_flight_index("availableflights.csv",seat[1]);

            if (rowToDelete == 0)
            {
                cout<<"index 0";
            }
            else
            {
                clearscreen();
    			cout << "====================================\n";
    			cout << "       Cancellation of Flight       \n";
    			cout << "====================================\n\n";
    			cout << "Cancel the flight of: " << name << endl;
    			cout << "Seat Number: " << seat[0] << endl;
    			cout << "Flight Number: " << seat[1] << endl;
    			cout << "\n------------------------------\n\n";
    			cout << "Are the information correct?\n";
    			cout << "1 - True\n";
    			cout << "2 - False\n\n";
    			cout << "Enter Choice: ";
                int choice;
                cin>>choice;
                if (choice == 1)
                {
                    revert_seat("availableflights.csv", name, flightindex, seat[0], seat[1]);
                    delete_row("passengerflights.csv", name_indx("passengerflights.csv", name));
                    press_enter();
                }
                else
                {   
                    clearscreen();
                    cout<<"RETURN TO MAIN MENU!\n";
                    press_enter();
                }
            }
			break;
		case 4:
            run_promo = true;
            promo();
            content = readCSV("Promos.csv");
            cout<<"\nSelect Promo Destination: ";
            cin>>destination;
            printing();

            book_seat("availableflights.csv", destination);

			break;
		case 5:
			Abt();
			break;
		case 6:
            clearscreen();
            flag = false;
            cout<<"THANK YOU FOR USING BSU Airline!";
			break;
		default:
			cout<<"INVALID PROMPT!.";
            press_enter();
    }
	}
}

int cancel_find_flight_index(string filename, string destination)
{   /*The cancel_find_flight_index function reads a CSV file and searches for a specific destination. It returns the index of the flight number */

    vector<vector<string>> content = readCSV(filename);
    int idx; // gets the flight num index based on destination
    for (int i = 1; i < content.size(); i++)
    {
        if (content[i][0].find(destination) != string::npos)
        {
            idx = i;
            return idx;
        }
    }
    return -1;
}

int ask_promo(string destination)
{   /*The ask_promo function reads a CSV file named "Promos.csv" and searches for a specific destination. It retrieves the corresponding promo price*/
    vector<vector<string>> content = readCSV("Promos.csv");
    string price; // stores the price of flight stored in flightprices.csv (promos)
    int price_int;
    for (int i = 1; i<content.size(); i++)
    {
        if (content[i][1].find(destination)!=string::npos)
        {
            price = content[i][0].substr(0,2); //gets only the first 2 string indexes because string format is ex. 10%
        }
    }
    price_int = stoi(price);
    return price_int;
}

void printing() {
    SetConsoleCP(437);
    SetConsoleOutputCP(437);

    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\n\t\t\t\tLoading...";
    cout << "\n\t\t\t\t";

    for (int i = 0; i < 25; i++)
        cout << (char)bar1;

    cout << "\r";
    cout << "\t\t\t\t";
    for (int i = 0; i < 25; i++) {
        cout << (char)bar2;
        this_thread::sleep_for(chrono::milliseconds(150));
    }
    cout << "\n\t\t\t\t";
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
}

void signIn() {
    string username, password;
    cout << "=========================\n";
    cout << "        Sign In\n";     
    cout << "=========================\n\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    bool found = false;

    ifstream file("users.csv");
    if (file) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string storedUsername = line.substr(0, pos);
                string storedPassword = line.substr(pos + 1);
                if (storedUsername == username && storedPassword == password) {
                    found = true;
                    break;
                }
            }
        }
        file.close();
    } else {
        cout << "ERROR: FAILED TO OPEN USER DATA FILE!\n";
    }

    clearscreen();

    if (found) {
        cout << "SIGN IN SUCCESSFUL! WELCOME TO BSU Airlines!\n";
        sign_in_flag = false;
        printing();
    } else {
        cout << "INVALID USERNAME OR PASSWPRD. PLEASE TRY AGAIN!\n";
        press_enter();
    }
}

void signUp() {
    if (userCount == 10) {
        cout << "CANNOT CREATE MORE USER. MAXIMUM LIMIT REACH!\n";
        return;
    }

    string username, password;
    cout << "=========================\n";
    cout << "        Sign Up\n";
    cout << "=========================\n\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    users[userCount].username = username;
    users[userCount].password = password;
    userCount++;

    // Open the CSV file in append mode and write the user data
    ofstream file("users.csv", ios::app);
    if (file) {
        file << username << "," << password << "\n";
        file.close();
        cout << "Sign up successful!\n";
    } else {
        cout << "ERROR: FAILED TO OPEN USER DATA FILE!\n";
    }

    clearscreen();
}

void logOut() {
    clearscreen();
    cout << "LOGGED OUT SUCCESSFULLY!\n";
}

void delete_row(const string& filename, int row_index) {
    // the delete_row function deletes a row from the passengerflights.csv if the needed conditions were met

    // Read the CSV file into memory
    vector<vector<string>> data = readCSV(filename);

    // Check if row_index is valid
    if (row_index < 1 || row_index >= data.size()) {
        cout << "INVALID ROW INDEX!." << endl;
        return;
    }

    // Remove the row at row_index
    data.erase(data.begin() + row_index);

    // Overwrite the file with updated content
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); i++) {
                outputFile << row[i];
                if (i != row.size() - 1) {
                    outputFile << ",";
                }
            }
            outputFile << endl;
        }
        outputFile.close();
        // cout << "Row deleted successfully." << endl;

    } else {
        cout << "Could not open the file for writing." << endl;
    }
}

int name_indx(string filename, string name)
{   /*The name_indx function reads a CSV file and searches for a specific name within the data, then returns the index of the name.*/
    vector<vector<string>> content = readCSV(filename);

    for (int i = 1; i < content.size(); i++) { //checks if name inputted is inside the file, if yes then return its index
            if (content[i][0].find(name) != string::npos) {
                return i;
            }
    }
    cout<<"NAME NOT FOUND!";
    return -1;
}

vector<string> seat_indx(string filename, string name)
{
    vector<vector<string>> content = readCSV(filename);
    int idx_name = name_indx("passengerflights.csv", name);
    vector<string> data;

    data.push_back(content[idx_name][2]); //seat
    data.push_back(content[idx_name][1]);//flight num
    data.push_back(content[idx_name][4]); //seat index
    return data;

}

void revert_seat(const string& filename, string name, int flight_idx, string seats, string flightnum) {
    /*The revert_seat function reverts a seat booking by updating the seat value in the specified flight of a CSV file.*/
    vector<vector<string>> content = readCSV(filename);
    vector<string> s_idx = seat_indx("passengerflights.csv", name);
    
    int seat = stoi(s_idx[2]); //seat index
    for (int i = 1; i < content.size(); i++) {
        if (flight_idx == i) {  // flight_idx returns an index but it is compard to the flightnum
            content[flight_idx][seat] = s_idx[0];  // Assign the original seat value back
        }
    }

    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const auto& row : content) {
            for (size_t i = 0; i < row.size(); i++) {
                outputFile << row[i];
                if (i != row.size() - 1) {
                    outputFile << ",";
                }
            }
            outputFile << endl;
        }
        outputFile.close();
        clearscreen();
		cout << "====================== Cancellation of Flight ======================\n\n";
    	cout << "       Successfully Canceled the flight of: " << name << "\n\n";
    	cout << "====================================================================\n";

    } else {
        cout << "COULD NOT OPEN FILE FOR WRITING!" << endl;
    }
}
