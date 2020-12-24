// #define_CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include "book.h"
using namespace std;

Book::Book () {
}

Book::Book (string _ISBN, string _title, string _author) {
    ISBN = _ISBN;
    title = _title;
    author = _author;
}
Book::Book (string _ISBN, int _wholesaleCost, int _retailPrice, int _quantityOnHand, string _title, string _author, string _publisher, string _dateAdded){
    ISBN = _ISBN;
    title = _title;
    author = _author;
    publisher = _publisher;
    retailPrice = _retailPrice;
    wholesaleCost = _wholesaleCost;
    quantityOnHand = _quantityOnHand;
    dateAdded = _dateAdded;

}
Book::~Book() {

}

// Assignment operator overload
void Book:: operator = ( Book& b) {
    try {
    quantityOnHand = b.quantityOnHand;
    title = b.title;
    author = b.author;
    publisher = b.publisher;
    dateAdded = b.dateAdded;
    retailPrice = b.retailPrice;
    wholesaleCost = b.wholesaleCost;
    ISBN = b.ISBN;
    } catch(...) {
        quantityOnHand = 0;
        title = "";
        author = "";
        publisher = "";
        dateAdded = "";
        retailPrice = 0.0;
        wholesaleCost = 0.0;
        ISBN = "";
    }
}

// Integer cast operator overload
Book::operator int() {
    return stoi(ISBN.substr(2,9));
}

double Book:: getRetailValue() {
    
    return retailPrice * quantityOnHand;
    
}

double Book:: getWholesaleValue() {
    
    return wholesaleCost * quantityOnHand;
    
}

void Book:: print() {
    cout << "ISBN: " << ISBN << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Quantity on hand: " << quantityOnHand << endl;
    cout << "Date added: " << dateAdded << endl;
    cout << "Retail price: $" << retailPrice << endl;
    cout << "Wholesale cost: $" << wholesaleCost << endl;
    cout << endl;
}

// Comparison operator overload
bool Book:: operator == (const Book& b) {
    return (b.quantityOnHand == quantityOnHand) &
    (b.title == title) &
    (b.author == author) &
    (b.publisher == publisher) &
    (b.dateAdded == dateAdded) &
    (b.retailPrice == retailPrice) &
    (b.wholesaleCost == wholesaleCost) &
    (b.ISBN == ISBN);
}

// << operator overload
ostream& operator<<(ostream &os, Book& book) {
    
    os << "ISBN: " << book.getISBN() << endl;
    os << "Title: " << book.getTitle() << endl;
    os << "Author: " << book.getAuthor() << endl;
    os << "Publisher: " << book.getPublisher() << endl;
    os << "Quantity on hand: " << book.getQuantityOnHand() << endl;
    os << "Date added: " << book.getDateAdded() << endl;
    os << "Retail price: $" << book.getRetailPrice() << endl;
    os << "Wholesale cost: $" << book.getWholesaleCost() << endl;
    os << endl;
    return os;
    
}


// >> operator overload
istream& operator>>(istream &is, Book& book) {
    string contents;

    getline(is, contents, ',');
    book.setISBN(contents);

    getline(is, contents, ',');
    book.setTitle(contents);

    getline(is, contents, ',');
    book.setAuthor(contents);

    getline(is, contents, ',');
    book.setPublisher(contents);

    getline(is, contents, ',');
    book.setDateAdded(contents);

    // Demonstration of exception handling
    getline(is, contents, ',');
    try {
        book.setQuantityOnHand(stoi(contents));
    } catch (...) {
        book.setQuantityOnHand(0);
    }

    getline(is, contents, ',');
    try {
        book.setWholesaleCost(stod(contents));
    } catch (...) {
        book.setWholesaleCost(0.0);
    }

    getline(is, contents, ',');
    try {
        book.setRetailPrice(stod(contents));
    } catch(...) {
        book.setRetailPrice(0.0);
    }

    return is;

}
