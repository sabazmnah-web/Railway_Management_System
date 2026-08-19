#include "RailwaySystem.h"

Passenger::Passenger() {
    name = "";
    occupation = "";
    age = 0;
    gender = 'M';
    trainID = 0;
}

Passenger::Passenger(std::string n, std::string occ, int a, char g, int tID) {
    name = n;
    occupation = occ;
    age = a;
    gender = g;
    trainID = tID;
}


Train::Train() {
    trainID = 0;
    division = "";
    departureTime = 0;
    femaleSeats = 0;
    maleSeats = 0;
}

Train::Train(int id, std::string div, int depTime, int fSeats, int mSeats) {
    trainID = id;
    division = div;
    departureTime = depTime;
    femaleSeats = fSeats;
    maleSeats = mSeats;
}


WaitingPriorityQueue::WaitingPriorityQueue() {
    count = 0;
}

void WaitingPriorityQueue::enqueue(Passenger p) {
    if (count >= 50) return;
    int i = count - 1;
    while (i >= 0 && arr[i].age < p.age) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = p;
    count++;
}

Passenger WaitingPriorityQueue::dequeue() {
    if (isEmpty()) return Passenger();
    Passenger p = arr[0];
    for (int i = 0; i < count - 1; i++) {
        arr[i] = arr[i + 1];
    }
    count--;
    return p;
}

bool WaitingPriorityQueue::isEmpty() {
    return count == 0;
}

void WaitingPriorityQueue::displayWaitingList() {
    if (isEmpty()) {
        std::cout << "No passengers on the waiting list.\n";
        return;
    }
    std::cout << "\n--- Waiting List (Ordered by Priority / Age) ---\n";
    for (int i = 0; i < count; i++) {
        std::cout << "Waiting Position #" << (i + 1)
                  << " | Name: " << arr[i].name
                  << " | Age: " << arr[i].age
                  << " | Occupation: " << arr[i].occupation
                  << " | Train ID: " << arr[i].trainID
                  << " | Target: " << (arr[i].gender == 'F' || arr[i].gender == 'f' ? "Female Compartment" : "Male General Compartment")
                  << "\n";
    }
}


PassengerTree::PassengerTree() {
    root = NULL;
}

BSTNode* PassengerTree::insertRec(BSTNode* node, Passenger p) {
    if (node == NULL) return new BSTNode(p);
    if (p.age < node->passenger.age) {
        node->left = insertRec(node->left, p);
    } else {
        node->right = insertRec(node->right, p);
    }
    return node;
}

void PassengerTree::printInOrder(BSTNode* node) {
    if (node == NULL) return;
    printInOrder(node->left);

    std::cout << "Name: " << node->passenger.name
              << " | Age: " << node->passenger.age
              << " | Occupation: " << node->passenger.occupation
              << " | Gender: " << node->passenger.gender
              << " | Train ID: " << node->passenger.trainID
              << " | Compartment: " << (node->passenger.gender == 'F' || node->passenger.gender == 'f'
                                        ? "Female Compartment"
                                        : "Male General Compartment")
              << "\n";

    printInOrder(node->right);
}

BSTNode* PassengerTree::findMin(BSTNode* node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

BSTNode* PassengerTree::deleteRec(BSTNode* node, std::string name, int tID, bool &found, Passenger &deletedPassenger) {
    if (node == NULL) return NULL;


    if (node->passenger.name == name && node->passenger.trainID == tID) {
        found = true;
        deletedPassenger = node->passenger;

        if (node->left == NULL) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == NULL) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }


        BSTNode* temp = findMin(node->right);
        node->passenger = temp->passenger;
        node->right = deleteRec(node->right, temp->passenger.name, temp->passenger.trainID, found, deletedPassenger);
        return node;
    }


    node->left = deleteRec(node->left, name, tID, found, deletedPassenger);
    if (!found) {
        node->right = deleteRec(node->right, name, tID, found, deletedPassenger);
    }
    return node;
}

bool PassengerTree::removePassenger(std::string name, int tID, Passenger &deletedPassenger) {
    bool found = false;
    root = deleteRec(root, name, tID, found, deletedPassenger);
    return found;
}

void PassengerTree::insert(Passenger p) {
    root = insertRec(root, p);
}

void PassengerTree::display() {
    printInOrder(root);
}


TrainList::TrainList() {
    head = NULL;
}

TrainList::~TrainList() {
    Node<Train>* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void TrainList::insert(Train t) {
    Node<Train>* newNode = new Node<Train>(t);
    newNode->next = head;
    head = newNode;
}

Node<Train>* TrainList::getHead() {
    return head;
}

void TrainList::display() {
    Node<Train>* temp = head;
    while (temp != NULL) {
        int hours = temp->data.departureTime / 100;
        int mins = temp->data.departureTime % 100;

        std::cout << "Train ID: " << temp->data.trainID
                  << " | Destination: " << temp->data.division
                  << " | Departure: " << (hours < 10 ? "0" : "") << hours << ":" << (mins < 10 ? "0" : "") << mins
                  << " | Female Compartment Seats: " << temp->data.femaleSeats
                  << " | Male General Compartment Seats: " << temp->data.maleSeats << "\n";
        temp = temp->next;
    }
}


void RailwaySystem::addTrain(int id, std::string div, int depTime, int fSeats, int mSeats) {
    if (id >= 1 && id <= 20) {
        trains.insert(Train(id, div, depTime, fSeats, mSeats));
    }
}

void RailwaySystem::showTrains() {
    trains.display();
}

void RailwaySystem::searchTrain(std::string div) {
    Node<Train>* temp = trains.getHead();
    bool found = false;
    while (temp != NULL) {
        if (temp->data.division == div) {
            int hours = temp->data.departureTime / 100;
            int mins = temp->data.departureTime % 100;

            std::cout << "Train Found! ID: " << temp->data.trainID
                      << " | Departure: " << (hours < 10 ? "0" : "") << hours << ":" << (mins < 10 ? "0" : "") << mins
                      << " | Female Seats: " << temp->data.femaleSeats
                      << " | Male Seats: " << temp->data.maleSeats << "\n";
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        std::cout << "No trains found for destination: " << div << "\n";
    }
}

void RailwaySystem::bookTicket(Passenger p) {
    Node<Train>* temp = trains.getHead();
    while (temp != NULL) {
        if (temp->data.trainID == p.trainID) {
            bool isFemale = (p.gender == 'F' || p.gender == 'f');

            if (isFemale && temp->data.femaleSeats > 0) {
                temp->data.femaleSeats--;
                passengerRecords.insert(p);
                std::cout << "\nBooking successful for " << p.name << "! Assigned to: Female Compartment\n";
            }
            else if (!isFemale && temp->data.maleSeats > 0) {
                temp->data.maleSeats--;
                passengerRecords.insert(p);
                std::cout << "\nBooking successful for " << p.name << "! Assigned to: Male General Compartment\n";
            }
            else {
                std::cout << "\nNo seats available in the requested compartment for Train " << p.trainID
                          << ". Adding " << p.name << " to the priority waiting list.\n";
                waitingList.enqueue(p);
            }
            return;
        }
        temp = temp->next;
    }
    std::cout << "Invalid Train ID.\n";
}

void RailwaySystem::cancelTicket(std::string name, int tID) {
    Passenger deletedPassenger;
    bool isCancelled = passengerRecords.removePassenger(name, tID, deletedPassenger);

    if (isCancelled) {

        Node<Train>* temp = trains.getHead();
        while (temp != NULL) {
            if (temp->data.trainID == tID) {
                if (deletedPassenger.gender == 'F' || deletedPassenger.gender == 'f') {
                    temp->data.femaleSeats++;
                    std::cout << "\nTicket successfully cancelled for " << name
                              << ". Returned 1 seat to Female Compartment (Train " << tID << ").\n";
                } else {
                    temp->data.maleSeats++;
                    std::cout << "\nTicket successfully cancelled for " << name
                              << ". Returned 1 seat to Male General Compartment (Train " << tID << ").\n";
                }
                return;
            }
            temp = temp->next;
        }
    } else {
        std::cout << "\nCancellation failed: No confirmed passenger record found with Name '"
                  << name << "' on Train ID " << tID << ".\n";
    }
}

void RailwaySystem::showPassengers() {
    std::cout << "\n CONFIRMED PASSENGER RECORDS \n";
    passengerRecords.display();

    std::cout << "\n WAITING LIST RECORDS \n";
    waitingList.displayWaitingList();
}
