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

SortedArrayList::SortedArrayList() { count = 0; }

void SortedArrayList::insert(Train t) {
    if (count >= 50) return;
    int i = count - 1;
    // Keep array sorted by trainID
    while (i >= 0 && arr[i].trainID > t.trainID) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = t;
    count++;
}

Train* SortedArrayList::findByID(int id) {
    for (int i = 0; i < count; i++) {
        if (arr[i].trainID == id) return &arr[i];
    }
    return NULL;
}

void SortedArrayList::display() {
    for (int i = 0; i < count; i++) {
        int hours = arr[i].departureTime / 100;
        int mins = arr[i].departureTime % 100;
        std::cout << "Train ID: " << arr[i].trainID
                  << " | Destination: " << arr[i].division
                  << " | Departure: " << (hours < 10 ? "0" : "") << hours << ":" << (mins < 10 ? "0" : "") << mins
                  << " | Female Seats: " << arr[i].femaleSeats
                  << " | Male Seats: " << arr[i].maleSeats << "\n";
    }
}

int SortedArrayList::getSize() { return count; }
Train SortedArrayList::getAt(int index) { return arr[index]; }

SortedLinkedList::SortedLinkedList() { head = NULL; }

SortedLinkedList::~SortedLinkedList() {
    SortedLLNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void SortedLinkedList::insertSortedByTime(Train t) {
    SortedLLNode* newNode = new SortedLLNode(t);
    if (head == NULL || head->data.departureTime >= t.departureTime) {
        newNode->next = head;
        head = newNode;
        return;
    }
    SortedLLNode* current = head;
    while (current->next != NULL && current->next->data.departureTime < t.departureTime) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void SortedLinkedList::display() {
    SortedLLNode* temp = head;
    while (temp != NULL) {
        int hours = temp->data.departureTime / 100;
        int mins = temp->data.departureTime % 100;
        std::cout << "Departure: " << (hours < 10 ? "0" : "") << hours << ":" << (mins < 10 ? "0" : "") << mins
                  << " | Train ID: " << temp->data.trainID
                  << " | Destination: " << temp->data.division << "\n";
        temp = temp->next;
    }
}

CancellationStack::CancellationStack() { top = NULL; }

CancellationStack::~CancellationStack() {
    while (!isEmpty()) {
        pop();
    }
}

void CancellationStack::push(Passenger p) {
    StackNode* newNode = new StackNode(p);
    newNode->next = top;
    top = newNode;
}

Passenger CancellationStack::pop() {
    if (isEmpty()) return Passenger();
    StackNode* temp = top;
    Passenger p = temp->data;
    top = top->next;
    delete temp;
    return p;
}

bool CancellationStack::isEmpty() { return top == NULL; }

void CancellationStack::displayHistory() {
    if (isEmpty()) {
        std::cout << "No cancellation history available.\n";
        return;
    }
    std::cout << "\nCancellation History\n";
    StackNode* temp = top;
    while (temp != NULL) {
        std::cout << "Cancelled Passenger: " << temp->data.name
                  << " | Train ID: " << temp->data.trainID
                  << " | Age: " << temp->data.age << "\n";
        temp = temp->next;
    }
}

WaitingPriorityQueue::WaitingPriorityQueue() { count = 0; }

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

bool WaitingPriorityQueue::isEmpty() { return count == 0; }

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
                  << " | Train ID: " << arr[i].trainID << "\n";
    }
}

PassengerTree::PassengerTree() { root = NULL; }

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
              << " | Train ID: " << node->passenger.trainID << "\n";
    printInOrder(node->right);
}

BSTNode* PassengerTree::findMin(BSTNode* node) {
    while (node && node->left != NULL) node = node->left;
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

void PassengerTree::insert(Passenger p) { root = insertRec(root, p); }
void PassengerTree::display() { printInOrder(root); }

void RailwaySystem::addTrain(int id, std::string div, int depTime, int fSeats, int mSeats) {
    Train t(id, div, depTime, fSeats, mSeats);
    sortedArrayTrains.insert(t);
    sortedLLTrains.insertSortedByTime(t);
}

void RailwaySystem::showTrains() {
    std::cout << "\n ALL TRAINS\n";
    sortedArrayTrains.display();
}

void RailwaySystem::showTrainsSortedByTime() {
    std::cout << "\nALL TRAINS \n";
    sortedLLTrains.display();
}

void RailwaySystem::searchByIdOrDestination(int id, std::string div) {
    bool found = false;
    for (int i = 0; i < sortedArrayTrains.getSize(); i++) {
        Train t = sortedArrayTrains.getAt(i);
        if (t.trainID == id || t.division == div) {
            std::cout << "Train Found! ID: " << t.trainID << " | Dest: " << t.division << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "No trains found.\n";
}

void RailwaySystem::searchByTimeOrDestination(int depTime, std::string div) {
    bool found = false;
    for (int i = 0; i < sortedArrayTrains.getSize(); i++) {
        Train t = sortedArrayTrains.getAt(i);
        if (t.departureTime == depTime || t.division == div) {
            std::cout << "Train Found! ID: " << t.trainID << " | Time: " << t.departureTime << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "No trains found.\n";
}

void RailwaySystem::bookTicket(Passenger p) {
    Train* t = sortedArrayTrains.findByID(p.trainID);
    if (t != NULL) {
        bool isFemale = (p.gender == 'F' || p.gender == 'f');
        if (isFemale && t->femaleSeats > 0) {
            t->femaleSeats--;
            passengerRecords.insert(p);
            std::cout << "\nBooking successful for " << p.name << " (Female Compartment)\n";
        } else if (!isFemale && t->maleSeats > 0) {
            t->maleSeats--;
            passengerRecords.insert(p);
            std::cout << "\nBooking successful for " << p.name << " (Male Compartment)\n";
        } else {
            std::cout << "\nNo seats available. Adding " << p.name << " to priority waiting list.\n";
            waitingList.enqueue(p);
        }
    } else {
        std::cout << "Invalid Train ID.\n";
    }
}

void RailwaySystem::cancelTicket(std::string name, int tID) {
    Passenger deletedPassenger;
    bool isCancelled = passengerRecords.removePassenger(name, tID, deletedPassenger);

    if (isCancelled) {
        cancellationLog.push(deletedPassenger);

        Train* t = sortedArrayTrains.findByID(tID);
        if (t != NULL) {
            if (deletedPassenger.gender == 'F' || deletedPassenger.gender == 'f') t->femaleSeats++;
            else t->maleSeats++;
            std::cout << "\nTicket successfully cancelled for " << name << ". Recorded to stack log.\n";
        }
    } else {
        std::cout << "\nCancellation failed: Record not found.\n";
    }
}

void RailwaySystem::showPassengers() {
    std::cout << "\n CONFIRMED PASSENGER RECORDS \n";
    passengerRecords.display();
    std::cout << "\n WAITING LIST RECORDS \n";
    waitingList.displayWaitingList();
}

void RailwaySystem::showCancellationHistory() {
    cancellationLog.displayHistory();
}
