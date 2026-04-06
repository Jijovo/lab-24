//Ezzat Mohamadein | ComSc 210 | Lab 24
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();
    
    //test add, display, and delete functions
    set<Goat> trip;
    add_goat(trip, names, colors);
    add_goat(trip, names, colors);
    add_goat(trip, names, colors);
    display_trip(trip);
    int choice = main_menu();
    while (choice != 4) {
        switch (choice) {
            case 1: add_goat(trip, names, colors); break;
            case 2: delete_goat(trip); break;
            case 3: display_trip(trip); break;
        }
        choice = main_menu();
    }

    //test extra constructors
    /*Goat g1 = Goat("guy");
    Goat g2 = Goat("dude", 5);
    Goat g3 = Goat("person", 10, "white");
    cout << g1.get_name() << " " << g1.get_age() << " " << g1.get_color() << endl;
    cout << g2.get_name() << " " << g2.get_age() << " " << g2.get_color() << endl;
    cout << g3.get_name() << " " << g3.get_age() << " " << g3.get_color() << endl;
    */

    //test main menu
    /*int choice = main_menu();
    cout << "You chose: " << choice << endl;
    */


    return 0;
}

//main menu function
int main_menu() {
    //output choices
    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List Goats" << endl;
    cout << "[4] Exit" << endl;
    cout << "Choice: ";
    //get input
    int c;
    cin >> c;
    //validate input
    while (c < 1 || c > 4) {
        cout << "Invalid choice. Please enter a number between 1 and 4: ";
        cin >> c;
    }
    cout << endl;
    return c;
}
//add goat function
void add_goat(set<Goat> &trip, string names[], string colors[]) {
    //generate random name, age, color
    string name = names[rand() % SZ_NAMES];
    int age = rand() % MAX_AGE + 1;
    string color = colors[rand() % SZ_COLORS];
    //create new goat and add to trip
    Goat new_goat(name, age, color);
    trip.insert(new_goat);
}
//display trip function
void display_trip(set<Goat> trip) {
    //check if trip is empty
    if (trip.empty()) {
        cout << "No goats to display." << endl;
        return;
    }
    //output header
    cout << left << setw(20) << "Number" << setw(10) << "Name" << setw(10) << "Age" << setw(20) << "Color" << endl;
    //output each goat
    int i = 1;
    string num = "[" + to_string(i) + "]";
    for (const auto &goat : trip) {
        cout << left << setw(20) << num << setw(10) << goat.get_name() << setw(10) << goat.get_age() << setw(20) << goat.get_color() << endl;
        i++;
         num = "[" + to_string(i) + "]";
    }
}
//delete goat function
void delete_goat(set<Goat> &trip) {
    //check if trip is empty
    if (trip.empty()) {
        cout << "No goats to delete." << endl;
        return;
    }
    //display goats and get selection
    display_trip(trip);
    cout << "Enter the number of the goat to delete: ";
    int choice;
    cin >> choice;
    //validate input
    while (choice < 1 || choice > trip.size()) {
        cout << "Invalid choice. Please enter a number between 1 and " << trip.size() << ": ";
        cin >> choice;
    }
    //delete selected goat
    auto it = trip.begin();
    advance(it, choice - 1);
    trip.erase(it);
}