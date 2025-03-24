#include <iostream>
#include <string>

using namespace std;

class IFlight {
public:
    virtual void showFlightInfo() const = 0;
    virtual ~IFlight() = default;
};

class Flight : public IFlight {
protected:
    string flightNumber;
    string destination;
    int freeSeats;
    static int totalFlights;

public:
    Flight(string number, string dest, int seats = 0)
        : flightNumber{number}, destination{dest}, freeSeats{seats} {
        totalFlights++;
        cout << "Flight constructor called for " << flightNumber << " to " << destination << endl;
    }

    virtual ~Flight() {
        totalFlights--;
        cout << "Flight destructor called for " << flightNumber << endl;
    }

    Flight(const Flight &other)
        : flightNumber{other.flightNumber}, destination{other.destination}, freeSeats{other.freeSeats} {
        totalFlights++;
        cout << "Flight copy constructor called for " << flightNumber << endl;
    }

    Flight(Flight &&other) noexcept
        : flightNumber{move(other.flightNumber)}, destination{move(other.destination)}, freeSeats{other.freeSeats} {
        other.freeSeats = 0;
        totalFlights++;
        cout << "Flight move constructor called for " << flightNumber << endl;
    }

    Flight& operator=(const Flight &rhs) {
        if (this != &rhs) {
            flightNumber = rhs.flightNumber;
            destination = rhs.destination;
            freeSeats = rhs.freeSeats;
            cout << "Flight COPY ASSIGNMENT OPERATOR called for " << flightNumber << endl;
        }
        return *this;
    }

    Flight& operator=(Flight &&rhs) noexcept {
        if (this != &rhs) {
            flightNumber = move(rhs.flightNumber);
            destination = move(rhs.destination);
            freeSeats = rhs.freeSeats;
            rhs.freeSeats = 0;
            cout << "Flight MOVE ASSIGNMENT OPERATOR called for " << flightNumber << endl;
        }
        return *this;
    }

    void addSeats(int seats) {
        if (seats > 0) {
            freeSeats += seats;
            cout << seats << " seats added to flight " << flightNumber << ". Total available: " << freeSeats << endl;
        } else {
            cout << "Invalid seat count for flight " << flightNumber << endl;
        }
    }

    virtual bool reserveSeat() {
        if (freeSeats > 0) {
            --freeSeats;
            return true;
        }
        cout << "No seats available on flight " << flightNumber << endl;
        return false;
    }

    int getAvailableSeats() const { return freeSeats; }

    static void staticFlightInfo() {
        cout << "Total active flights: " << totalFlights << endl;
    }

    virtual void showFlightInfo() const override {
        cout << "Flight " << flightNumber << " to " << destination << ", available seats: " << freeSeats << endl;
    }
    virtual void flightType() const {
        cout << "General flight information.\n";
    }
};

int Flight::totalFlights = 0;

class InternationalFlight final : public Flight {
private:
    string countryCode;

public:
    InternationalFlight(string number, string dest, string code, int seats = 0)
        : Flight(number, dest, seats), countryCode{code} {
        cout << "InternationalFlight constructor called for " << number << " to " << dest << endl;
    }

    ~InternationalFlight() override {
        cout << "InternationalFlight destructor called" << endl;
    }

    void showFlightInfo() const override {
        cout << "International Flight " << flightNumber << " to " << destination << " (" << countryCode << "), seats: " << freeSeats << endl;
    }
    void flightType() const override {
        cout << "This is an international flight.\n";
    }
};

class DomesticFlight final : public Flight {
public:
    DomesticFlight(string number, string dest, int seats = 0) : Flight(number, dest, seats) {
        cout << "DomesticFlight constructor called for " << number << " to " << dest << endl;
    }

    ~DomesticFlight() override {
        cout << "DomesticFlight destructor called" << endl;
    }

    void showFlightInfo() const override {
        cout << "Domestic Flight " << flightNumber << " to " << destination << ", seats: " << freeSeats << endl;
    }
    void flightType() const override {
        cout << "This is a domestic flight.\n";
    }
};

class Passenger {
private:
    string name;
    Flight *flight;

public:
    Passenger(string passengerName, Flight *f) : name{passengerName}, flight{f} {
        cout << "Passenger constructor called for " << name << endl;
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
        cout << "Passenger destructor called for " << name << endl;
    }
};

int main() {


    cout << "\n=== динамічне зв'язування ===\n";
    Flight* flightPtr = new InternationalFlight("IF777", "Rome", "IT", 4);
    flightPtr->showFlightInfo();
    flightPtr->flightType();
    delete flightPtr;

    cout << "\n=== Base Class через посилання ===\n";
    InternationalFlight intFlight("IF999", "Tokyo", "JP", 10);
    Flight &refFlight = intFlight;
    refFlight.showFlightInfo();

    cout << "\n=== Add Seats ===\n";
    InternationalFlight internationalFlight1("IF123", "Paris", "FR", 5);
    DomesticFlight domesticFlight1("DF456", "Kyiv", 3);
    internationalFlight1.addSeats(3);
    domesticFlight1.addSeats(2);

    cout << "\n=== Passenger Booking ===\n";
    Passenger passenger1("John", &internationalFlight1);
    passenger1.showPassengerInfo();
    passenger1.bookFlight();

    Passenger passenger2("Alice", &domesticFlight1);
    passenger2.showPassengerInfo();
    passenger2.bookFlight();

    cout << "\n=== Copy/Move constructor and Other ===\n";
    Flight fly1("A101", "New York", 50);
    Flight fly2("B202", "London", 30);
    fly2 = fly1;
    Flight fly3("C303", "Tokyo", 20);
    fly3 = move(fly1);

    cout << "\n=== Static Method Binding ===\n";
    Flight::staticFlightInfo();
    cout << endl;
    return 0;
}
