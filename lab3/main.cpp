#include <iostream>
#include <string>

using namespace std;

class Flight {
private:
    string flightNumber;
    string destination;
    int freeSeats;
    static int totalFlights; // Статичне поле

public:
    Flight() : flightNumber{"Unknown"}, destination{"Unknown"}, freeSeats{0} {
        totalFlights++;
    }

    Flight(string number, string dest, int seats = 0)
        : flightNumber{number}, destination{dest}, freeSeats{seats} {
        totalFlights++;
    }

    Flight(const Flight &other) // Конструктор копіювання
        : flightNumber(other.flightNumber), destination(other.destination), freeSeats(other.freeSeats) {
        cout << "Copy constructor called for " << flightNumber << endl;
    }

    Flight(Flight &&other) noexcept // Конструктор переміщення
        : flightNumber(move(other.flightNumber)), destination(move(other.destination)), freeSeats(other.freeSeats) {
        other.freeSeats = 0;
        cout << "Move constructor called for " << flightNumber << endl;
    }

    ~Flight() {
        cout << "Flight " << flightNumber << " is being deleted.\n";
        totalFlights--;
    }

    void displayInfo() const { // Використання const-методу
        cout << "Flight: " << flightNumber << " to " << destination
             << " Available Seats: " << freeSeats << endl;
    }

    Flight& operator++() { // Унарний оператор (збільшення місць)
        ++freeSeats;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Flight &f) { // Перевантаження <<
        os << "Flight: " << f.flightNumber << " to " << f.destination
           << " Available Seats: " << f.freeSeats;
        return os;
    }

    static int getTotalFlights() { // Статичний метод
        return totalFlights;
    }
};

int Flight::totalFlights = 0; // Ініціалізація статичного поля

class Passenger {
private:
    string name;
    int age;

public:
    Passenger() : name{"Unknown"}, age{0} {}

    Passenger(string newName, int newAge) : name{newName}, age{newAge} {}

    Passenger(const Passenger &other) // Конструктор копіювання
        : name(other.name), age(other.age) {}

    void showInfo() const { // Використання const-методу
        cout << "Passenger: " << name << " Age: " << age << endl;
    }
};

class Booking {
private:
    string ID;
    string passengerName;
    string flightNumber;

public:
    Booking() : ID{"None"}, passengerName{"None"}, flightNumber{"None"} {}

    Booking(string id, string pName, string fNumber = "Unknown")
        : ID{id}, passengerName{pName}, flightNumber{fNumber} {}

    Booking(const Booking &other) // Конструктор копіювання
        : ID(other.ID), passengerName(other.passengerName), flightNumber(other.flightNumber) {}

    void printBooking() const {
        cout << "Booking ID: " << ID << ", Passenger: " << passengerName
             << ", Flight: " << flightNumber << endl;
    }
};

int main() {
    Flight f1("AB123", "Porto", 89);
    Flight f2 = f1; // Виклик конструктора копіювання
    Flight f3 = move(f1); // Виклик конструктора переміщення

    Passenger p1("Alice", 19);
    Booking b1("BKG001", "Alice", "AB123");

    f2.displayInfo();
    cout << f3 << endl; // Перевантажений оператор <<

    cout << "Total flights: " << Flight::getTotalFlights() << endl; // Використання статичного методу

    return 0;
}
