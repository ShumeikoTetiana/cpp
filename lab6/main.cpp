#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

using namespace std;

class Flight {
protected:
    string flightNumber;
    string destination;
    int freeSeats;

public:
    Flight(string number, string dest, int seats)
        : flightNumber{number}, destination{dest}, freeSeats{seats} {}

    void showFlightInfo() const {
        cout << "Flight " << flightNumber << " to " << destination
             << ", Available seats: " << freeSeats << endl;
    }

    bool reserveSeat() {
        if (freeSeats > 0) {
            --freeSeats;
            cout << "Seat successfully reserved on flight " << flightNumber << "!" << endl;
            return true;
        }
        cout << "No available seats on flight " << flightNumber << "!" << endl;
        return false;
    }

    void saveToFile(ofstream &out) const {
        out << flightNumber << " " << destination << " " << freeSeats << endl;
    }
};

vector<shared_ptr<Flight>> flights;

void loadFlights() {
    ifstream file("flights.txt");

    if (!file) {
        cout << "No saved flights found." << endl;
        return;
    }
    string number, destination;
    int seats;
    while (file >> number >> destination >> seats) {
        flights.push_back(make_shared<Flight>(number, destination, seats));
    }
    file.close();
    cout << "Flights loaded successfully!" << endl;
}

void saveFlights() {
    ofstream file("flights.txt");
    for (const auto &flight : flights) {
        flight->saveToFile(file);
    }
    file.close();
    cout << "Flights saved successfully!" << endl;
}

void adminMenu() {
    string password;
    cout << "Enter admin password: ";
    cin >> password;
    if (password != "cat") {
        cout << "Incorrect password!" << endl;
        return;
    }

    int choice;
    do {
        cout << "\nAdmin Menu:\n1. Add Flight\n2. Show Flights\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            string num, dest;
            int seats;
            cout << "Enter flight number, destination, and available seats: ";
            cin >> num >> dest >> seats;
            flights.push_back(make_shared<Flight>(num, dest, seats));
            saveFlights();
            cout << "Flight added successfully!" << endl;
        } else if (choice == 2) {
            if (flights.empty()) {
                cout << "No flights available." << endl;
            } else {
                for (const auto &flight : flights) flight->showFlightInfo();
            }
        }
    } while (choice != 3);
}

void userMenu() {
    int choice;
    do {
        cout << "\nUser Menu:\n1. View Flights\n2. Book a Seat\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            if (flights.empty()) {
                cout << "No flights available." << endl;
            } else {
                for (const auto &flight : flights) flight->showFlightInfo();
            }
        } else if (choice == 2) {
            string num;
            cout << "Enter flight number: ";
            cin >> num;
            bool found = false;
            for (const auto &flight : flights) {
                if (flight->reserveSeat()) {
                    saveFlights();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Flight not found or no available seats!" << endl;
            }
        }
    } while (choice != 3);
}

int main() {
    loadFlights();
    int choice;
    do {
        cout << "\nMain Menu:\n1. Admin Login\n2. User Mode\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) adminMenu();
        else if (choice == 2) userMenu();
    } while (choice != 3);
    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}
