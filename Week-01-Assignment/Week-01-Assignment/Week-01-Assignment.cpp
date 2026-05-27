// Week-01-Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

class Author {
private:
    string name;
    string email;
    char gender;

public:
    Author(string name, string email, char gender) {
        this->name = name;
        this->email = email;
        this->gender = gender;
    }

    string getName() {
        return name;
    }

    string getEmail() {
        return email;
    }

    void setEmail(string email) {
        this->email = email;
    }

    char getGender() {
        return gender;
    }

    string print() {
        string result = name + " (";
        result += gender;
        result += ") at " + email;
        return result;
    }
};

class Book {
private:
    string name;
    Author author;
    double price;

public:
    Book(string name, Author author, double price) : author(author) {
        this->name = name;
        this->price = price;
    }

    string getName() {
        return name;
    }

    Author getAuthor() {
        return author;
    }

    double getPrice() {
        return price;
    }

    void setPrice(double price) {
        this->price = price;
    }

    string print() {
        return name + " by " + author.print();
    }
};

int main() {
    Author author1("Mike", "mJones@somewhere.com", 'm');

    Book book1("Introduction to Programming", author1, 59.99);

    cout << "Author Information:" << endl;
    cout << author1.print() << endl;

    cout << endl;

    cout << "Book Information:" << endl;
    cout << book1.print() << endl;
    cout << "Price: $" << book1.getPrice() << endl;

    cout << endl;

    book1.setPrice(49.99);

    cout << "Updated Book Price: $" << book1.getPrice() << endl;

    return 0;
}// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
