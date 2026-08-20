#include <iostream>
#include <string>
#include "RailwaySystem.h"

int main() {
    RailwaySystem sys;

    // 7 Divisions of Bangladesh with 2 Departure Times each (14 Trains total)
    // Format: addTrain(ID, Destination, DepartureTime, FemaleSeats, MaleSeats)
    sys.addTrain(1,  "Dhaka",      700,  5, 10);
    sys.addTrain(2,  "Dhaka",      1700, 5, 10);
    sys.addTrain(3,  "Chittagong", 830,  4,  8);
    sys.addTrain(4,  "Chittagong", 1830, 4,  8);
    sys.addTrain(5,  "Rajshahi",   900,  6, 12);
    sys.addTrain(6,  "Rajshahi",   1900, 6, 12);
    sys.addTrain(7,  "Khulna",     1000, 5, 10);
    sys.addTrain(8,  "Khulna",     2000, 5, 10);
    sys.addTrain(9,  "Barisal",    1100, 3,  7);
    sys.addTrain(10, "Barisal",    2100, 3,  7);
    sys.addTrain(11, "Sylhet",     1200, 4,  9);
    sys.addTrain(12, "Sylhet",     2200, 4,  9);
    sys.addTrain(13, "Rangpur",    1300, 6, 14);
    sys.addTrain(14, "Rangpur",    2300, 6, 14);

    int choice = 0;
    while (choice != 7) {
        std::cout << "\n  RAILWAY TICKET RESERVATION SYSTEM\n";
        std::cout << "1. View All Trains\n";
        std::cout << "2. Search Train by Train ID or Destination\n";
        std::cout << "3. Search Train by Departure Time or Destination\n";
        std::cout << "4. Book a Ticket\n";
        std::cout << "5. View Passenger List & Waiting Numbers\n";
        std::cout << "6. Cancel a Ticket\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            sys.showTrains();
        }
        else if (choice == 2) {
            int subChoice;
            std::cout << "\n1. Search by Train ID\n";
            std::cout << "2. Search by Destination\n";
            std::cout << "Enter choice: ";
            std::cin >> subChoice;

            if (subChoice == 1) {
                int id;
                std::cout << "Enter Train ID: ";
                std::cin >> id;
                sys.searchByIdOrDestination(id, "");
            } else {
                std::string dest;
                std::cout << "Enter Destination Division: ";
                std::cin >> dest;
                sys.searchByIdOrDestination(-1, dest);
            }
        }
        else if (choice == 3) {
            int subChoice;
            std::cout << "\n1. Search by Departure Time (e.g., 700 or 1700)\n";
            std::cout << "2. Search by Destination\n";
            std::cout << "Enter choice: ";
            std::cin >> subChoice;

            if (subChoice == 1) {
                int depTime;
                std::cout << "Enter Departure Time (HHMM format, e.g. 830): ";
                std::cin >> depTime;
                sys.searchByTimeOrDestination(depTime, "");
            } else {
                std::string dest;
                std::cout << "Enter Destination Division: ";
                std::cin >> dest;
                sys.searchByTimeOrDestination(-1, dest);
            }
        }
        else if (choice == 4) {
            std::string name, occ;
            int age, tID;
            char gender;

            std::cout << "Enter Name: ";
            std::cin >> name;
            std::cout << "Enter Occupation: ";
            std::cin >> occ;
            std::cout << "Enter Age: ";
            std::cin >> age;
            std::cout << "Enter Gender (M/F): ";
            std::cin >> gender;
            std::cout << "Enter Train ID: ";
            std::cin >> tID;

            Passenger p(name, occ, age, gender, tID);
            sys.bookTicket(p);
        }
        else if (choice == 5) {
            sys.showPassengers();
        }
        else if (choice == 6) {
            std::string name;
            int tID;

            std::cout << "Enter Passenger Name to Cancel: ";
            std::cin >> name;
            std::cout << "Enter Train ID: ";
            std::cin >> tID;

            sys.cancelTicket(name, tID);
        }
        else if (choice == 7) {
            std::cout << "Exiting system\n";
        }
        else {
            std::cout << "Invalid choice. Select between 1 and 7.\n";
        }
    }

    return 0;
}
