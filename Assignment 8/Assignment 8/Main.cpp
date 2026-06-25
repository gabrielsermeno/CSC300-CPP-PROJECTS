#include <iostream>
#include <string>
using namespace std;

// Customer class
class Customer {
public:
    int customerID;
    string name;
    string email;
    string phoneNumber;

    Customer(int id, string n, string e, string phone) {
        customerID = id;
        name = n;
        email = e;
        phoneNumber = phone;
    }

    void displayCustomer() {
        cout << "Customer ID: " << customerID << endl;
        cout << "Customer Name: " << name << endl;
        cout << "Email: " << email << endl;
    }
};

// Event class
class Event {
public:
    int eventID;
    string eventName;
    string eventDate;
    string location;
    int availableTickets;
    double ticketPrice;

    Event(int id, string name, string date, string loc, int tickets, double price) {
        eventID = id;
        eventName = name;
        eventDate = date;
        location = loc;
        availableTickets = tickets;
        ticketPrice = price;
    }

    bool checkAvailability(int quantity) {
        if (quantity <= availableTickets) {
            return true;
        }
        else {
            return false;
        }
    }

    void removeTickets(int quantity) {
        availableTickets = availableTickets - quantity;
    }

    void displayEvent() {
        cout << "Event ID: " << eventID << endl;
        cout << "Event Name: " << eventName << endl;
        cout << "Date: " << eventDate << endl;
        cout << "Location: " << location << endl;
        cout << "Available Tickets: " << availableTickets << endl;
        cout << "Ticket Price: $" << ticketPrice << endl;
    }
};

// Order class
class Order {
public:
    int orderID;
    int customerID;
    int eventID;
    int quantity;
    double totalAmount;
    string status;

    Order(int oID, int cID, int eID, int q) {
        orderID = oID;
        customerID = cID;
        eventID = eID;
        quantity = q;
        totalAmount = 0;
        status = "Created";
    }

    void calculateTotal(double price) {
        totalAmount = quantity * price;
    }

    void confirmOrder() {
        status = "Confirmed";
    }

    void displayOrder() {
        cout << "Order ID: " << orderID << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Total Amount: $" << totalAmount << endl;
        cout << "Order Status: " << status << endl;
    }
};

// Payment class
class Payment {
public:
    int paymentID;
    string paymentMethod;
    double amount;
    string paymentStatus;

    Payment(int id, string method) {
        paymentID = id;
        paymentMethod = method;
        amount = 0;
        paymentStatus = "Pending";
    }

    bool processPayment(double total) {
        amount = total;

        if (amount > 0) {
            paymentStatus = "Approved";
            return true;
        }
        else {
            paymentStatus = "Declined";
            return false;
        }
    }

    void displayPayment() {
        cout << "Payment ID: " << paymentID << endl;
        cout << "Payment Method: " << paymentMethod << endl;
        cout << "Payment Status: " << paymentStatus << endl;
    }
};

// Ticket class
class Ticket {
public:
    int ticketID;
    int eventID;
    int customerID;
    string barcode;
    string seatNumber;
    string ticketStatus;

    Ticket(int tID, int eID, int cID) {
        ticketID = tID;
        eventID = eID;
        customerID = cID;
        barcode = "BAR" + to_string(ticketID);
        seatNumber = "General Admission";
        ticketStatus = "Valid";
    }

    void displayTicket() {
        cout << "Ticket ID: " << ticketID << endl;
        cout << "Barcode: " << barcode << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Ticket Status: " << ticketStatus << endl;
    }
};

// Maintenance Request class
// This class is for the special feature: Maintenance Tracking
class MaintenanceRequest {
public:
    int requestID;
    string issueDescription;
    string status;
    string priority;

    MaintenanceRequest(int id, string issue) {
        requestID = id;
        issueDescription = issue;
        status = "Reported";
        priority = "High";
    }

    void displayRequest() {
        cout << "Maintenance Request ID: " << requestID << endl;
        cout << "Issue: " << issueDescription << endl;
        cout << "Status: " << status << endl;
        cout << "Priority: " << priority << endl;
    }
};

// Ticket System class
// This class controls the main ticket purchase transaction
class TicketSystem {
public:
    bool systemWorking;

    TicketSystem() {
        systemWorking = true;
    }

    void setSystemWorking(bool working) {
        systemWorking = working;
    }

    void purchaseTicket(Customer customer, Event& event, int quantity) {
        cout << "\n--------------------------------------" << endl;
        cout << "Starting Purchase Ticket Transaction" << endl;
        cout << "--------------------------------------" << endl;

        cout << "Customer selected event: " << event.eventName << endl;
        cout << "Number of tickets requested: " << quantity << endl;

        bool ticketsAvailable = event.checkAvailability(quantity);

        if (ticketsAvailable == true && systemWorking == true) {
            cout << "\nTickets are available." << endl;
            cout << "System is working." << endl;

            Order order1(1001, customer.customerID, event.eventID, quantity);
            order1.calculateTotal(event.ticketPrice);

            Payment payment1(2001, "Credit Card");
            bool paid = payment1.processPayment(order1.totalAmount);

            if (paid == true) {
                order1.confirmOrder();
                event.removeTickets(quantity);

                Ticket ticket1(3001, event.eventID, customer.customerID);

                cout << "\nSUCCESSFUL TRANSACTION" << endl;
                order1.displayOrder();
                payment1.displayPayment();

                cout << "\nDigital Ticket Created:" << endl;
                ticket1.displayTicket();

                cout << "\nDigital ticket sent to: " << customer.email << endl;
                cout << "Tickets remaining for this event: " << event.availableTickets << endl;
            }
            else {
                cout << "Payment was declined. Ticket was not created." << endl;
            }
        }
        else if (systemWorking == false) {
            cout << "\nALTERNATIVE TRANSACTION" << endl;
            cout << "The ticket system or ticket device is under maintenance." << endl;

            MaintenanceRequest request1(4001, "Ticket device is not working.");
            request1.displayRequest();

            cout << "Customer Message: Ticket purchase is temporarily unavailable." << endl;
        }
        else {
            cout << "\nThere are not enough tickets available." << endl;
            cout << "Customer Message: Purchase cannot be completed." << endl;
        }

        cout << "--------------------------------------" << endl;
        cout << "End Transaction" << endl;
        cout << "--------------------------------------" << endl;
    }
};

int main() {
    cout << "CSC300 Assignment 8" << endl;
    cout << "Event Ticket Distribution System" << endl;
    cout << "Special Feature: Maintenance Tracking" << endl;

    Customer customer1(1, "Gabriel Sermeno", "gabriel@email.com", "555-1234");

    Event event1(101, "Summer Music Festival", "07/15/2026", "San Diego Arena", 100, 45.00);

    TicketSystem system1;

    cout << "\nDEMO 1: Successful Transaction" << endl;
    system1.setSystemWorking(true);
    system1.purchaseTicket(customer1, event1, 2);

    cout << "\n\nDEMO 2: Alternative Transaction - Maintenance Tracking" << endl;
    system1.setSystemWorking(false);
    system1.purchaseTicket(customer1, event1, 1);

    return 0;
}