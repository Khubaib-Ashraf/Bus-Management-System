#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Class to represent a Bus
class Bus {
private:
    int busNumber;
    string route;
    int totalSeats;
    vector<bool> seats; // true = booked, false = available

public:
    Bus(int number, string route, int seats) : busNumber(number), route(route), totalSeats(seats) {
        seats = max(seats, 0); // Ensure seats are non-negative
        this->seats.resize(seats, false); // Initialize all seats as available
    }

    int getBusNumber() const {
        return busNumber;
    }

    string getRoute() const {
        return route;
    }

    int getTotalSeats() const {
        return totalSeats;
    }

    int getAvailableSeats() const {
        return count(seats.begin(), seats.end(), false);
    }

    bool bookSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats) {
            cout << "Invalid seat number!" << endl;
            return false;
        }
        if (seats[seatNumber - 1]) {
            cout << "Seat " << seatNumber << " is already booked!" << endl;
            return false;
        }
        seats[seatNumber - 1] = true;
        cout << "Seat " << seatNumber << " booked successfully!" << endl;
        return true;
    }

    bool cancelSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats) {
            cout << "Invalid seat number!" << endl;
            return false;
        }
        if (!seats[seatNumber - 1]) {
            cout << "Seat " << seatNumber << " is not booked!" << endl;
            return false;
        }
        seats[seatNumber - 1] = false;
        cout << "Seat " << seatNumber << " canceled successfully!" << endl;
        return true;
    }

    void displaySeats() const {
        cout << "Seat Status for Bus " << busNumber << " (" << route << "):" << endl;
        for (int i = 0; i < totalSeats; i++) {
            cout << "Seat " << (i + 1) << ": " << (seats[i] ? "Booked" : "Available") << endl;
        }
    }
};

// Class to manage the Bus Management System
class BusManagementSystem {
private:
    vector<Bus> buses;

public:
    void addBus(int number, string route, int seats) {
        buses.push_back(Bus(number, route, seats));
        cout << "Bus " << number << " added successfully!" << endl;
    }

    void displayAllBuses() const {
        if (buses.empty()) {
            cout << "No buses available!" << endl;
            return;
        }
        for (const auto& bus : buses) {
            cout << "Bus Number: " << bus.getBusNumber() << ", Route: " << bus.getRoute()
                 << ", Total Seats: " << bus.getTotalSeats() << ", Available Seats: " << bus.getAvailableSeats() << endl;
        }
    }

    Bus* findBus(int number) {
        for (auto& bus : buses) {
            if (bus.getBusNumber() == number) {
                return &bus;
            }
        }
        return nullptr;
    }

    void bookTicket(int busNumber, int seatNumber) {
        Bus* bus = findBus(busNumber);
        if (bus) {
            bus->bookSeat(seatNumber);
        } else {
            cout << "Bus " << busNumber << " not found!" << endl;
        }
    }

    void cancelTicket(int busNumber, int seatNumber) {
        Bus* bus = findBus(busNumber);
        if (bus) {
            bus->cancelSeat(seatNumber);
        } else {
            cout << "Bus " << busNumber << " not found!" << endl;
        }
    }

    void displayBusSeats(int busNumber) const {
        for (const auto& bus : buses) {
            if (bus.getBusNumber() == busNumber) {
                bus.displaySeats();
                return;
            }
        }
        cout << "Bus " << busNumber << " not found!" << endl;
    }
};

// Main function to interact with the system
int main() {
    BusManagementSystem system;
    int choice;

    while (true) {
        cout << "\nBus Management System\n";
        cout << "1. Add Bus\n";
        cout << "2. Display All Buses\n";
        cout << "3. Book Ticket\n";
        cout << "4. Cancel Ticket\n";
        cout << "5. Display Bus Seats\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int number, seats;
                string route;
                cout << "Enter Bus Number: ";
                cin >> number;
                cout << "Enter Route: ";
                cin.ignore();
                getline(cin, route);
                cout << "Enter Total Seats: ";
                cin >> seats;
                system.addBus(number, route, seats);
                break;
            }
            case 2:
                system.displayAllBuses();
                break;
            case 3: {
                int busNumber, seatNumber;
                cout << "Enter Bus Number: ";
                cin >> busNumber;
                cout << "Enter Seat Number: ";
                cin >> seatNumber;
                system.bookTicket(busNumber, seatNumber);
                break;
            }
            case 4: {
                int busNumber, seatNumber;
                cout << "Enter Bus Number: ";
                cin >> busNumber;
                cout << "Enter Seat Number: ";
                cin >> seatNumber;
                system.cancelTicket(busNumber, seatNumber);
                break;
            }
            case 5: {
                int busNumber;
                cout << "Enter Bus Number: ";
                cin >> busNumber;
                system.displayBusSeats(busNumber);
                break;
            }
            case 6:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
