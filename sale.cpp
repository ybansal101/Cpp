#include <iostream>
#include "sale.h"

// Polymorphism -- this function definition overrides the inherited print() function of the Book class
void Sale::print() {
    cout << "ISBN: " << ISBN << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Quantity on hand: " << quantityOnHand << endl;
    cout << "Date added: " << dateAdded << endl;
    cout << "Retail price: $" << retailPrice << endl;
    cout << "Wholesale cost: $" << wholesaleCost << endl;
    cout << "Total cost: " << getTotal() << endl;
    cout << endl;
}
