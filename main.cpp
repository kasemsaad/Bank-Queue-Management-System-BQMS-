#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Customer
{
public:
    int id;
    int servicetime;
    int waitingtime;
    Customer() {}
    Customer(int Id, int Servicetime, int Waitingtime = 0)
    {
        id = Id;
        servicetime = Servicetime;
        waitingtime = Waitingtime;
    }
};
/////////////////////////////////////////////////
class Teller
{
public:
    bool available;
    Teller()
    {
        available = true;
    }
};
///////////////////////////////////////////////////////////////////
class Queue
{
private:
    class Node
    {
    public:
        Customer data;
        Node *next;

        Node(Customer data)
        {
            this->data = data;
            next = NULL;
        }
    };

    Node *rear, *front;

public:
    Queue()
    {
        rear = front = NULL;
    }

    int enqueue(Customer data)
    {
        Node *node = new Node(data);
        if (front == NULL)
        {
            front = rear = node;
        }
        else
        {
            rear->next = node;
            rear = node;
        }
        return 1;
    }

    int dequeue(Customer &data)
    {
        if (front == NULL)
        {
            return 0;
        }
        Node *front2 = front;
        data = front2->data;
        front = front->next;
        delete front2;

        return 1;
    }

    bool empty()
    {
        return front == NULL;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BQMS
{
private:
    Queue customerqueue;
    vector<Teller> tellers;
    int totalcustomersserved;
    int totalwaitingtime;
    int totalservicetime;

public:
    BQMS(int numtellers)
    {
        totalcustomersserved = 0;
        totalwaitingtime = 0;
        totalservicetime = 0;

        for (int i = 0; i < numtellers; ++i)
        {
            tellers.push_back(Teller());
        }
    }
////////////////////////////////////////////////////////////////////////////////////////
    void enqueue(int customerId, int servicetime)
    {
        Customer customer(customerId, servicetime);
        customerqueue.enqueue(customer);
        cout << "Customer " << customerId << "\t" << " arrived the Bank " <<"==============="
             << "service time: " << servicetime << " minutes." << endl;
        dequeue();
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////
    void dequeue()
    {
        if (!customerqueue.empty())
        {
            Customer customer;
            customerqueue.dequeue(customer);
            addcustomerinteller(customer);
        }
        else
        {
            cout << "not found customers in the queue." << endl;
        }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////
    void addcustomerinteller(Customer customer)
    {
        int waitingtime = 0;
        int queueSize = customerqueue.empty();
        Queue tempqueue = customerqueue;

        while (!tempqueue.empty())
        {
            Customer tempCustomer;
            tempqueue.dequeue(tempCustomer);
            if (tempCustomer.id = customer.id)
            {
              break;
            }
            else
            {
               waitingtime += tempCustomer.servicetime;
            }
        }
        totalwaitingtime += waitingtime;
        for (int i = 0; i < tellers.size(); ++i)
        {
            if (tellers[i].available)
            {
                tellers[i].available = false;
                totalcustomersserved++;
                totalservicetime += customer.servicetime;
                cout << "customer " << customer.id << "\t"
                     << " is being served by Teller " << i + 1 << "." << endl;
                return;
            }
        }

        cout << "All tellers are busy " << customer.id << " is waiting for " << waitingtime << " minutes." << endl;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void display()
    {
        if (totalcustomersserved > 0)
        {
            cout << "avg waiting time: " << (totalwaitingtime / totalcustomersserved) << " minutes." << endl;
            cout << "avg service time: " << (totalservicetime / totalcustomersserved) << " minutes." << endl;
            cout << "percentage of customers served: " << (double(totalcustomersserved) / (totalcustomersserved + 1) * 100) << "%" << endl;

        }
        else
        {
            cout << "no customers served " << endl;
        }
                cout << "Total customers served: " << totalcustomersserved << endl;

    }
};
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    srand(time(0));

    int numtellers = 3;
    //     int numtellers = 5;

    BQMS bqms(numtellers);
    bqms.enqueue(1,2);
    bqms.enqueue(2,2);
    bqms.enqueue(3,2);
    bqms.enqueue(4,2);
    bqms.enqueue(5,2);
    bqms.enqueue(6,10);
    bqms.enqueue(7,18);
    bqms.enqueue(8,22);
    bqms.enqueue(9,18);
    bqms.enqueue(10,24);
    bqms.enqueue(11,6);
    bqms.display();

    return 0;
}
