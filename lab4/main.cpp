#include <iostream>
#include <string>

using namespace std;


class Flight {
private:
    string flightNumber;
    string destination;
    int freeSeats;

public:
    Flight(string number, string dest, int seats = 0)
        : flightNumber{number}, destination{dest}, freeSeats{seats} {
        cout << "\n" << "Flight constructor called for " << flightNumber << " to " << destination << endl;
    }

    Flight(const Flight &other)
        : flightNumber{other.flightNumber}, destination{other.destination}, freeSeats{other.freeSeats} {
        cout << "Flight copy constructor called for " << flightNumber << endl;
    }

    Flight(Flight &&other) noexcept
        : flightNumber{move(other.flightNumber)}, destination{move(other.destination)}, freeSeats{other.freeSeats} {
        other.freeSeats = 0;
        cout << "Flight move constructor called for " << flightNumber << endl;
    }

    // Оператор присвоєння копіювання
    Flight& operator=(const Flight &rhs) {
        if (this != &rhs) {
            flightNumber = rhs.flightNumber;
            destination = rhs.destination;
            freeSeats = rhs.freeSeats;
            cout  << "Flight copy assignment operator called for " << flightNumber << endl;
        }
        return *this;
    }

    // Оператор присвоєння переміщення
    Flight& operator=(Flight &&rhs) noexcept {
        if (this != &rhs) {
            flightNumber = move(rhs.flightNumber);
            destination = move(rhs.destination);
            freeSeats = rhs.freeSeats;
            rhs.freeSeats = 0;
            cout << "Flight move assignment operator called for " << flightNumber << endl;
        }
        return *this;
    }

    void addSeats(int seats) {
        freeSeats += seats;
    }

    bool reserveSeat() {
        if (freeSeats > 0) {
            --freeSeats;
            return true;
        } else {
            cout << "No seats available on flight " << flightNumber << endl;
            return false;
        }
    }

    int getAvailableSeats() const {
        return freeSeats;
    }

    ~Flight() {
        cout << "Flight destructor called for " << flightNumber  << endl;
    }
};

class InternationalFlight : public Flight {
private:
    string countryCode;

public:
    InternationalFlight(string number, string dest, string code, int seats = 0)
        : Flight(number, dest, seats), countryCode{code} {
        cout << "InternationalFlight constructor called for " << number << " to " << dest << ". Code " << countryCode << endl;
    }

    InternationalFlight(const InternationalFlight &other)
        : Flight(other), countryCode{other.countryCode} {
        cout << "InternationalFlight copy constructor called" << endl;
    }

    InternationalFlight(InternationalFlight &&other) noexcept
        : Flight(move(other)), countryCode{move(other.countryCode)} {
        cout << "InternationalFlight move constructor called" << endl;
    }

    ~InternationalFlight() {
        cout << "InternationalFlight destructor called" << endl;
    }
};

class DomesticFlight : public Flight {
public:
    DomesticFlight(string number, string dest, int seats = 0) : Flight(number, dest, seats) {
        cout << "DomesticFlight constructor called for " << number << " to " << dest << endl;
    }

    DomesticFlight(const DomesticFlight &other) : Flight(other) {
        cout << "DomesticFlight copy constructor called" << endl;
    }

    DomesticFlight(DomesticFlight &&other) noexcept : Flight(move(other)) {
        cout << "DomesticFlight move constructor called" << endl;
    }

    ~DomesticFlight() {
        cout << "\n" << "DomesticFlight destructor called" << endl;
    }
};

class Passenger {
private:
    string name;
    Flight *flight;                      // "Has-A" має місце

public:
    Passenger(string passengerName, Flight *f) : name{passengerName}, flight{f} {
        cout << "\n" << "Passenger constructor called for " << name << endl;
    }

    void bookFlight() {
        if (flight->reserveSeat()) {
            cout << name << " has successfully booked a seat on flight." << endl;
        }
    }

    void showPassengerInfo() const {
        cout << "Passenger: " << name << ", Flight available seats: " << flight->getAvailableSeats() << endl;
    }

    ~Passenger() {
        cout << "Passenger destructor called for " << name <<  endl;
    }
};

int main() {
    InternationalFlight internationalFlight1("IF123", "Paris", "FR", 5);
    internationalFlight1.addSeats(3);

    DomesticFlight domesticFlight1("DF456", "Kyiv", 3);
    domesticFlight1.addSeats(2);

    Passenger passenger1("John", &internationalFlight1);
    passenger1.showPassengerInfo();
    passenger1.bookFlight();

    Passenger passenger2("Alice", &domesticFlight1);
    passenger2.showPassengerInfo();
    passenger2.bookFlight();

    InternationalFlight f1 = internationalFlight1;  // Copy
    DomesticFlight f2 = move(domesticFlight1);

    return 0;
}
