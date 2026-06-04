#include <iostream>
#include <string>
using namespace std;

// Creating a class for Author.
class Author
{
// These variables can only be used inside of the Author class. 
private:
    string name;
    string email;
    char gender;

// These variables can be used outside of the private Author class.
public:
    Author(string n, string e, char g)
    {
        name = n;
        email = e;
        gender = g;
    }

    // making some functions to return the values.
    string getName()
    {
        return name;
    }

    string getEmail()
    {
        return email;
    }

    // Sets email values.
    void setEmail(string e)
    {
        email = e;
    }

    char getGender()
    {
        return gender;
    }
    
    // print the author info.
    void print()
    {
        cout << name << " (" << gender << ") at " << email << endl;
    }
};

// I pretty much just followed the same format as the for the Author class above.
class Book
{
private:
    string name;
    Author author;
    double price;

public:
    Book(string n, Author a, double p) : author(a)
    {
        name = n;
        price = p;
    }

    string getName()
    {
        return name;
    }

    Author getAuthor()
    {
        return author;
    }

    double getPrice()
    {
        return price;
    }

    void setPrice(double p)
    {
        price = p;
    }

    void print()
    {
        cout << name << " by ";
        author.print();
    }
};


int main()
{
    // making an object from the class Author.  And hard setting the values to the instructions.
    Author a1("Mike Jones", "mJones@somewhere.com", 'm');

    // printing the object info.
    cout << "Author:" << endl;
    a1.print();

    // making an object from the class book.  And hard setting the values to the instructions.
    Book b1("Introduction to Programming", a1, 49.99);

    // printing the object info.
    cout << endl;
    cout << "Book:" << endl;
    b1.print();
    cout << "Price: $" << b1.getPrice() << endl;

    // setting the price of the book.
    cout << endl;
    cout << "Changing price..." << endl;
    b1.setPrice(39.99);

    // printing the price.
    cout << "Book after price change:" << endl;
    b1.print();
    cout << "Price: $" << b1.getPrice() << endl;

    return 0;
}