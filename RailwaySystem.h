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

class SortedArrayList {
private:
    Train arr[50];
    int count;
public:
    SortedArrayList();
    void insert(Train t);
    Train* findByID(int id);
    void display();
    int getSize();
    Train getAt(int index);
};

class SortedLLNode {
public:
    Train data;
    SortedLLNode* next;
    SortedLLNode(Train val) {
        data = val;
        next = NULL;
    }
};

class SortedLinkedList {
private:
    SortedLLNode* head;
public:
    SortedLinkedList();
    ~SortedLinkedList();
    void insertSortedByTime(Train t);
    void display();
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

class CancellationStack {
private:
    StackNode* top;
public:
    CancellationStack();
    ~CancellationStack();
    void push(Passenger p);
    Passenger pop();
    bool isEmpty();
    void displayHistory();
};

// Existing Priority Queue and BST components
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

class RailwaySystem {
private:
    SortedArrayList sortedArrayTrains;  // Array-Based Sorted List
    SortedLinkedList sortedLLTrains;    // Linked List-Based Sorted List
    CancellationStack cancellationLog;  // Stack Data Structure
    WaitingPriorityQueue waitingList;   // Priority Queue
    PassengerTree passengerRecords;     // BST
public:
    void addTrain(int id, std::string div, int depTime, int fSeats, int mSeats);
    void showTrains();
    void showTrainsSortedByTime();
    void searchByIdOrDestination(int id, std::string div);
    void searchByTimeOrDestination(int depTime, std::string div);
    void bookTicket(Passenger p);
    void cancelTicket(std::string name, int tID);
    void showPassengers();
    void showCancellationHistory();
};

#endif
