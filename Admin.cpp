#include "Admin.h"
#include <iostream>

Admin::Admin(const std::string& username)
    : User(username) {}

void Admin::menu() {
    int choice;
    do {
        std::cout << "Admin Menu:\n";
        std::cout << "1. Add flight\n";
        std::cout << "2. Edit flight\n";
        std::cout << "3. Delete flight\n";
        std::cout << "4. List all flights\n";
        std::cout << "5. Find flight\n";
        std::cout << "6. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1: {
            int flightNumber;
            int day;
            int month;
            int time;
            int seats;
            std::string destination;
            std::cout << "Enter flight number\n";
            std::cin >> flightNumber;
            std::cout << "Enter destination\n";
            std::cin >> destination;
            std::cout << "Enter month\n";
            std::cin >> month;
            std::cout << "Enter day\n";
            std::cin >> day;
            std::cout << "Enter numbers of seats\n";
            std::cin >> seats;
            std::cout << "Enter departure time\n";
            std::cin >> time;
            addFlight(flightNumber, destination, day, month, time, seats);
            break;
        }
        case 2: {
            int flightNumber;
            std::cout << "Enter flight number: ";
            std::cin >> flightNumber;
            editFlight(flightNumber);
            break;
        }
        case 3: {
            int flightNumber;
            std::cout << "Enter flight number: ";
            std::cin >> flightNumber;
            deleteFlight(flightNumber);
            break;
        }
        case 4:
            listAllFlights();
            break;
        case 5:
            findFlight();
            break;
        case 6:
            std::cout << "Exiting admin panel.\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 6);
}