#ifndef RAILWAY_SYSTEM_H
#define RAILWAY_SYSTEM_H

#include <iostream>
#include <string>

class Passenger {
public:
    std::string name;
    std::string occupation;
    int age;
    char gender;
    int trainID;

    Passenger();
    Passenger(std::string n, std::string occ, int a, char g, int tID);
};

class Train {
public:
    int trainID;
    std::string division;
    int departureTime;
    int femaleSeats;
    int maleSeats;

    Train();
    Train(int id, std::string div, int depTime, int fSeats, int mSeats);
};

class TrainNode {
public:
    Train data;
    TrainNode* next;
    TrainNode(Train t) {
        data = t;
        next = NULL;
    }
};

class StackNode {
public:
    Passenger data;
    StackNode* next;
    StackNode(Passenger p) {
        data = p;
        next = NULL;
    }
};

class PassengerNode {
public:
    Passenger data;
    PassengerNode* next;
    PassengerNode(Passenger p) {
        data = p;
        next = NULL;
    }
};

class RailwaySystem {
private:
    TrainNode* trainHead;
    PassengerNode* passengerHead;
    Passenger waitingQueue[50];
    int queueCount;
    StackNode* stackTop;

public:
    RailwaySystem();
    ~RailwaySystem();

    void addTrain(int id, std::string div, int depTime, int fSeats, int mSeats);
    void showTrainsByID();
    void showTrainsByTime();
    void searchByTimeOrDestination(int depTime, std::string div);
    void bookTicket(Passenger p);
    void cancelTicket(std::string name, int tID);
    void showPassengers();
    void showCancellationHistory();
};

#endif
