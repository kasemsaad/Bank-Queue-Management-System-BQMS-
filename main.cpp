#include <iostream>
#include <queue>
#include <vector>
#include <ctime>

using namespace std;

// Customer structure
class Customer {
public:
    int id;
    int serviceTime;
    int waitingTime; // New attribute for waiting time

    // Constructor
    Customer(int _id, int _serviceTime, int _waitingTime = 0) : id(_id), serviceTime(_serviceTime), waitingTime(_waitingTime) {}
};

// Teller structure
struct Teller {
    bool available;

    // Constructor
    Teller() : available(true) {}
};

class BankQueueManagementSystem {
private:
    queue<Customer> customerQueue;
    vector<Teller> tellers;
    // Statistics
    int totalCustomersServed;
    int totalWaitingTime;
    int totalServiceTime;

public:
    BankQueueManagementSystem(int numTellers) : totalCustomersServed(0), totalWaitingTime(0), totalServiceTime(0) {
        // Initialize tellers
        for (int i = 0; i < numTellers; ++i) {
            tellers.push_back(Teller());
        }
    }

    void enqueueCustomer(int customerId) {
        int serviceTime = generateRandomServiceTime();
        Customer customer(customerId, serviceTime);
        customerQueue.push(customer);
        cout << "Customer " << customerId <<"\t" << " arrived the Bank " <<endl<<"service time: " << serviceTime << " minutes." << endl;
    }

    void dequeueCustomer() {
        if (!customerQueue.empty()) {
            Customer customer = customerQueue.front();
            customerQueue.pop();
            assignCustomerToTeller(customer);
        } else {
            cout << "No customers in the queue." << endl;
        }
    }

    void assignCustomerToTeller(Customer customer) {
        int waitingTime = 0;
        int queueSize = customerQueue.size();
        queue<Customer> tempQueue = customerQueue;

        while (!tempQueue.empty()) {
            Customer tempCustomer = tempQueue.front();
            tempQueue.pop();
            if (tempCustomer.id != customer.id) {
                waitingTime += tempCustomer.serviceTime;

            } else {
                break;
            }

        }

        for (int i = 0; i < tellers.size(); ++i) {
            if (tellers[i].available) { // Check if the teller is available
                tellers[i].available = false; // Mark the teller as busy
                totalCustomersServed++;
                totalServiceTime += customer.serviceTime;
                cout << "Customer " << customer.id <<"\t"<< " is being served by Teller " << i + 1 << "." << endl;
            //    totalWaitingTime += waitingTime; // Update total waiting time with the customer's waiting time
           //     customer.waitingTime = waitingTime;

                return;
            }


        }
    cout << "All tellers are busy. Customer " << customer.id << " is waiting" <<waitingTime<<"minutes."<< endl;


    }

    int generateRandomServiceTime() {
        // Generate random service time (between 5 and 15 minutes for example)
        return rand() % 11 + 5;
    }

    void displayStatistics() {
        cout << "Total customers served: " << totalCustomersServed << endl;
        if (totalCustomersServed > 0) {
            cout << "Average waiting time: " << (totalWaitingTime / totalCustomersServed) << " minutes." << endl;
            cout << "Average service time: " << (totalServiceTime / totalCustomersServed) << " minutes." << endl;
        } else {
            cout << "No customers served yet." << endl;
        }

    }
};

int main() {
    srand(time(0)); // Seed for random number generator

    int numTellers = 3;
   //  int numTellers = 5; // Number of tellers
    BankQueueManagementSystem bqms(numTellers);

    // Test the system
    bqms.enqueueCustomer(1);
        bqms.dequeueCustomer();

    bqms.enqueueCustomer(2);
        bqms.dequeueCustomer();

    bqms.enqueueCustomer(3);
        bqms.dequeueCustomer();

    bqms.enqueueCustomer(4);
        bqms.dequeueCustomer();

    bqms.enqueueCustomer(5);
        bqms.dequeueCustomer();

    bqms.enqueueCustomer(6);
        bqms.dequeueCustomer();

    bqms.enqueueCustomer(7);
        bqms.dequeueCustomer();

    bqms.enqueueCustomer(8);
    bqms.dequeueCustomer();


    bqms.displayStatistics();

    return 0;
}
