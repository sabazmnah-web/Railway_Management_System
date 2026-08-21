#include "RailwaySystem.h"

Passenger::Passenger() {
    name = ""; occupation = ""; age = 0; gender = 'M'; trainID = 0;
}

Passenger::Passenger(std::string n, std::string occ, int a, char g, int tID) {
    name = n; occupation = occ; age = a; gender = g; trainID = tID;
}

Train::Train() {
    trainID = 0; division = ""; departureTime = 0; femaleSeats = 0; maleSeats = 0;
}

Train::Train(int id, std::string div, int depTime, int fSeats, int mSeats) {
    trainID = id; division = div; departureTime = depTime; femaleSeats = fSeats; maleSeats = mSeats;
}

RailwaySystem::RailwaySystem() {
    trainHead = NULL;
    passengerHead = NULL;
    queueCount = 0;
    stackTop = NULL;
}

RailwaySystem::~RailwaySystem() {
    while (trainHead != NULL) {
        TrainNode* temp = trainHead;
        trainHead = trainHead->next;
        delete temp;
    }
    while (passengerHead != NULL) {
        PassengerNode* temp = passengerHead;
        passengerHead = passengerHead->next;
        delete temp;
    }
    while (stackTop != NULL) {
        StackNode* temp = stackTop;
        stackTop = stackTop->next;
        delete temp;
    }
}

void RailwaySystem::addTrain(int id, std::string div, int depTime, int fSeats, int mSeats) {
    Train t(id, div, depTime, fSeats, mSeats);
    TrainNode* newNode = new TrainNode(t);

    if (trainHead == NULL) {
        trainHead = newNode;
    } else {
        TrainNode* temp = trainHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void RailwaySystem::showTrainsByID() {
    Train tempArr[50];
    int count = 0;
    TrainNode* curr = trainHead;

    while (curr != NULL) {
        tempArr[count++] = curr->data;
        curr = curr->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (tempArr[j].trainID > tempArr[j + 1].trainID) {
                Train temp = tempArr[j];
                tempArr[j] = tempArr[j + 1];
                tempArr[j + 1] = temp;
            }
        }
    }

    std::cout << "\n--- ALL TRAINS (Sorted by ID) ---\n";
    for (int i = 0; i < count; i++) {
        int h = tempArr[i].departureTime / 100;
        int m = tempArr[i].departureTime % 100;
        std::cout << "Train ID: " << tempArr[i].trainID
                  << " | Destination: " << tempArr[i].division
                  << " | Departure: " << (h < 10 ? "0" : "") << h << ":" << (m < 10 ? "0" : "") << m
                  << " | Female Seats: " << tempArr[i].femaleSeats
                  << " | Male Seats: " << tempArr[i].maleSeats << "\n";
    }
}

void RailwaySystem::showTrainsByTime() {
    Train tempArr[50];
    int count = 0;
    TrainNode* curr = trainHead;

    while (curr != NULL) {
        tempArr[count++] = curr->data;
        curr = curr->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (tempArr[j].departureTime > tempArr[j + 1].departureTime) {
                Train temp = tempArr[j];
                tempArr[j] = tempArr[j + 1];
                tempArr[j + 1] = temp;
            }
        }
    }

    std::cout << "\nALL TRAINS\n";
    for (int i = 0; i < count; i++) {
        int h = tempArr[i].departureTime / 100;
        int m = tempArr[i].departureTime % 100;
        std::cout << "Departure: " << (h < 10 ? "0" : "") << h << ":" << (m < 10 ? "0" : "") << m
                  << " | Train ID: " << tempArr[i].trainID
                  << " | Destination: " << tempArr[i].division
                  << " | Female Seats: " << tempArr[i].femaleSeats
                  << " | Male Seats: " << tempArr[i].maleSeats << "\n";
    }
}

void RailwaySystem::searchByTimeOrDestination(int depTime, std::string div) {
    TrainNode* temp = trainHead;
    bool found = false;

    while (temp != NULL) {
        if (temp->data.departureTime == depTime || temp->data.division == div) {
            int h = temp->data.departureTime / 100;
            int m = temp->data.departureTime % 100;

            std::cout << "Train Found! ID: " << temp->data.trainID
                      << " | Destination: " << temp->data.division
                      << " | Departure: " << (h < 10 ? "0" : "") << h << ":" << (m < 10 ? "0" : "") << m
                      << " | Female Seats: " << temp->data.femaleSeats
                      << " | Male Seats: " << temp->data.maleSeats << "\n";
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        std::cout << "No trains found matching the search criteria.\n";
    }
}

void RailwaySystem::bookTicket(Passenger p) {
    TrainNode* temp = trainHead;

    while (temp != NULL) {
        if (temp->data.trainID == p.trainID) {
            bool isFemale = (p.gender == 'F' || p.gender == 'f');

            if (isFemale && temp->data.femaleSeats > 0) {
                temp->data.femaleSeats--;

                PassengerNode* newPass = new PassengerNode(p);
                newPass->next = passengerHead;
                passengerHead = newPass;

                std::cout << "\nBooking successful for " << p.name << "! (Female Compartment)\n";
                return;
            }
            else if (!isFemale && temp->data.maleSeats > 0) {
                temp->data.maleSeats--;

                PassengerNode* newPass = new PassengerNode(p);
                newPass->next = passengerHead;
                passengerHead = newPass;

                std::cout << "\nBooking successful for " << p.name << "! (Male General Compartment)\n";
                return;
            }
            else {
                if (queueCount < 50) {
                    int i = queueCount - 1;
                    while (i >= 0 && waitingQueue[i].age < p.age) {
                        waitingQueue[i + 1] = waitingQueue[i];
                        i--;
                    }
                    waitingQueue[i + 1] = p;
                    queueCount++;

                    std::cout << "\nNo seats available. Added " << p.name << " to the Priority Waiting List.\n";
                } else {
                    std::cout << "\nWaiting List Full!\n";
                }
                return;
            }
        }
        temp = temp->next;
    }
    std::cout << "\nInvalid Train ID.\n";
}

void RailwaySystem::cancelTicket(std::string name, int tID) {
    PassengerNode* curr = passengerHead;
    PassengerNode* prev = NULL;
    bool found = false;
    Passenger deletedPassenger;

    while (curr != NULL) {
        if (curr->data.name == name && curr->data.trainID == tID) {
            found = true;
            deletedPassenger = curr->data;

            if (prev == NULL) {
                passengerHead = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (found) {
        StackNode* newStackNode = new StackNode(deletedPassenger);
        newStackNode->next = stackTop;
        stackTop = newStackNode;

        TrainNode* temp = trainHead;
        while (temp != NULL) {
            if (temp->data.trainID == tID) {
                if (deletedPassenger.gender == 'F' || deletedPassenger.gender == 'f') {
                    temp->data.femaleSeats++;
                } else {
                    temp->data.maleSeats++;
                }
                std::cout << "\nTicket successfully cancelled for " << name << ". Seat reallocated.\n";
                return;
            }
            temp = temp->next;
        }
    } else {
        std::cout << "\nCancellation failed: No passenger found with Name '" << name << "' on Train ID " << tID << ".\n";
    }
}

void RailwaySystem::showPassengers() {
    std::cout << "\nCONFIRMED PASSENGERS\n";
    PassengerNode* temp = passengerHead;
    if (temp == NULL) {
        std::cout << "No confirmed passengers.\n";
    }
    while (temp != NULL) {
        std::cout << "Name: " << temp->data.name
                  << " | Age: " << temp->data.age
                  << " | Occupation: " << temp->data.occupation
                  << " | Gender: " << temp->data.gender
                  << " | Train ID: " << temp->data.trainID << "\n";
        temp = temp->next;
    }

    std::cout << "\nWAITING LIST\n";
    if (queueCount == 0) {
        std::cout << "No passengers on the waiting list.\n";
    } else {
        for (int i = 0; i < queueCount; i++) {
            std::cout << "Waiting Position" << (i + 1)
                      << " | Name: " << waitingQueue[i].name
                      << " | Age: " << waitingQueue[i].age
                      << " | Train ID: " << waitingQueue[i].trainID << "\n";
        }
    }
}

void RailwaySystem::showCancellationHistory() {
    std::cout << "\nCANCELLATION HISTORY\n";
    if (stackTop == NULL) {
        std::cout << "No cancellation history available.\n";
        return;
    }
    StackNode* temp = stackTop;
    while (temp != NULL) {
        std::cout << "Cancelled Passenger: " << temp->data.name
                  << " | Train ID: " << temp->data.trainID
                  << " | Age: " << temp->data.age
                  << " | Occupation: " << temp->data.occupation << "\n";
        temp = temp->next;
    }
}
