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


template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node(T val) {
        data = val;
        next = NULL;
    }
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

class WaitingPriorityQueue {
private:
    Passenger arr[50];
    int count;
public:
    WaitingPriorityQueue();
    void enqueue(Passenger p);
    Passenger dequeue();
    bool isEmpty();
    void displayWaitingList();
};

class BSTNode {
public:
    Passenger passenger;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Passenger p) {
        passenger = p;
        left = NULL;
        right = NULL;
    }
};

class PassengerTree {
private:
    BSTNode* root;
    BSTNode* insertRec(BSTNode* node, Passenger p);
    void printInOrder(BSTNode* node);
    BSTNode* findMin(BSTNode* node);
    BSTNode* deleteRec(BSTNode* node, std::string name, int tID, bool &found, Passenger &deletedPassenger);
public:
    PassengerTree();
    void insert(Passenger p);
    void display();
    bool removePassenger(std::string name, int tID, Passenger &deletedPassenger);
};

class TrainList {
private:
    Node<Train>* head;
public:
    TrainList();
    ~TrainList();
    void insert(Train t);
    Node<Train>* getHead();
    void display();
};

class RailwaySystem {
private:
    TrainList trains;
    WaitingPriorityQueue waitingList;
    PassengerTree passengerRecords;
public:
    void addTrain(int id, std::string div, int depTime, int fSeats, int mSeats);
    void showTrains();
    void searchTrain(std::string div);
    void bookTicket(Passenger p);
    void cancelTicket(std::string name, int tID);
    void showPassengers();
};

#endif
