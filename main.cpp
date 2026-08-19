#include <iostream>
#include <string>
#include "RailwaySystem.h"

int main() {
    RailwaySystem sys;

    sys.addTrain(1,  "Dhaka",      700,  5, 10);
    sys.addTrain(2,  "Chittagong", 830,  1,  1);
    sys.addTrain(3,  "Rajshahi",   1015, 6, 14);
    sys.addTrain(4,  "Khulna",     1200, 4,  8);
    sys.addTrain(5,  "Barisal",    1430, 5, 10);
    sys.addTrain(6,  "Sylhet",     1600, 3,  9);
    sys.addTrain(7,  "Rangpur",    1800, 6, 14);
    sys.addTrain(8,  "Mymensingh", 2000, 8, 17);

    int choice = 0;
    while (choice != 6) {

        std::cout << "  RAILWAY TICKET RESERVATION SYSTEM\n";
        std::cout << "1. View All Trains\n";
        std::cout << "2. Search Train by Destination\n";
        std::cout << "3. Book a Ticket\n";
        std::cout << "4. View Passenger List & Waiting Numbers\n";
        std::cout << "5. Cancel a Ticket\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            sys.showTrains();
        }
        else if (choice == 2) {
            std::string dest;
            std::cout << "Enter destination: ";
            std::cin >> dest;
            sys.searchTrain(dest);
        }
        else if (choice == 3) {
            std::string name, occ;
            int age, tID;
            char gender;

            std::cout << "Enter Name: ";
            std::cin >> name;
            std::cout << "Enter Occupation: ";
            std::cin >> occ;
            std::cout << "Enter Age: ";
            std::cin >> age;
            std::cout << "Enter Gender: ";
            std::cin >> gender;
            std::cout << "Enter Train ID: ";
            std::cin >> tID;

            Passenger p(name, occ, age, gender, tID);
            sys.bookTicket(p);
        }
        else if (choice == 4) {
            sys.showPassengers();
        }
        else if (choice == 5) {
            std::string name;
            int tID;

            std::cout << "Enter Passenger Name to Cancel: ";
            std::cin >> name;
            std::cout << "Enter Train ID: ";
            std::cin >> tID;

            sys.cancelTicket(name, tID);
        }
        else if (choice == 6) {
            std::cout << "Exiting system\n";
        }
        else {
            std::cout << "Invalid choice. Select between 1 and 6.\n";
        }
    }

    return 0;
}
