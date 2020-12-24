// #define_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "sale.h"
using namespace std;


// This global variable stores the initial number of books in the inventory
const int SIZE = 50;

// This template function is meant to be a partial replacement of std::remove.
template <class ForwardIterator, class T>
  ForwardIterator removeFunction (ForwardIterator first, ForwardIterator last, const T& val) {
  ForwardIterator result = first;
  // This while loop checks whether anything in the FowardIterator-type object contains the element that needs to be removed, and copies everything that doesn't need to be removed to the object that will be returned from the function
    while (first!=last) {
    if (!(*first == val)) {
      *result = *first;
      ++result;
    }
    ++first;
  }
  return result;
}


// The following three lines are function templates for functions that will be defined later in the program
void reportModule();
void inventoryDatabaseModule();
void mainMenu();


// This structure is meant to be a partial replacement of std::map.
template <typename T>
struct KeyValuePair {
    T key;
    int value;
};

// This is a standard function that reverses an array.
template <typename T>
void reverse(T arr[], int n) {
    // This for loop swaps the element at index i in the array with the element at index (n-1-i), where n is the number of elements in the array.
    for (int low = 0, high = n - 1; low < high; low++, high--) {
        T temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
}

// This is the selection sort function, which is used for sorting arrays throughout the program. It is not the most efficient sorting function, but with only 50 books in the inventory it's good enough.
template <typename T>
void selectionSort(T arr[], int n) {
    int i, j, min;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        T temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

// This class represents the entire book inventory of the bookshop
class Inventory {
    int numberOfBooks;
    double retailValue;
    double wholesaleValue;
    Book *books;
    
public:
    
    // Getters and setters for number of books
    int getNumberOfBooks() const {
        return numberOfBooks;
    }
    void setNumberOfBooks(int _numberOfBooks) {
        numberOfBooks = _numberOfBooks;
    }
    // Getters and setters for retail value
    double getRetailValue() const {
        return retailValue;
    }
    void setRetailValue(double _retailValue) {
        retailValue = _retailValue;
    }
    
    // getters and setters for wholesale value
    double getWholesaleValue() const {
        return wholesaleValue;
    }
    void setWholesaleValue(double _retailValue) {
        retailValue = _retailValue;
    }
    // The setBook function sets a specific book's value.
    void setBook(Book book, int index) {
        books[index] = book;
    }
     // Get a specific book.
    Book getBook(int index) const {
        return books[index];
    }
    
     // Member function to create an array of books.
     void createBookArray(int size) {
         numberOfBooks = size;
         books = new Book[size];
         for (int i = 0; i < size; i++) {
            Book book = Book("", "", "");
            books[i] = book;
         }
     }
    
    // This function calculates the total wholesale value of the inventory
    double inventoryWholesaleValue() {
        double wholesaleValue = 0.0;
        for (int i = 0; i < numberOfBooks; i++)
            wholesaleValue = wholesaleValue + books[i].getWholesaleValue();
        return wholesaleValue;
    }

    // This function calculates the total retail value of the inventory
    double inventoryRetailValue() {
        double retailValue = 0.0;
        for (int i = 0; i < numberOfBooks; i++)
            retailValue = retailValue + books[i].getRetailValue();
        return retailValue;
    }
    
    // This function prints the books in the inventory sorted by quantity
    void printBooksSortedByQuantity() {
        
        // The statement below declares a variable that will hold the sorted array of books
        Book* booksNew = new Book[numberOfBooks];
        
        // The statement below declares a variable that will hold the quantity of each book in the inventory
        int* quantityArray = new int[numberOfBooks];
        
        // The statement below declares a variable that will hold the index of each book in the inventory
        int* indicesArray = new int[numberOfBooks];
        
        // The statement below declares a variable that will hold an array of KeyValuePair objects that store the index of each book and the corresponding quantity.
        KeyValuePair<int>* keyValuePairs = new KeyValuePair<int>[numberOfBooks];
        
        // The for loop below fills the dateArray variable with the quantity of each book
        for (int i = 0; i < numberOfBooks; i++)
            quantityArray[i] = books[i].getQuantityOnHand();
        
        // The for loop below fills the keyValuePairs variable with the quantity and index of each book
        for (int i = 0; i < numberOfBooks; i++) {
            keyValuePairs[i].key = quantityArray[i];
            keyValuePairs[i].value = i;
        }
        
        // The statement below sorts the quantityArray variable
        selectionSort<int>(quantityArray,numberOfBooks);
        
        // The statement below reverses the quantityArray variable
        reverse<int>(quantityArray,numberOfBooks);
        
        // The for loop below assigns a value to each element of the indicesArray variable at location i that is equal to the index of the ith most plentiful book of the inventory
        for (int j = 0; j < numberOfBooks; j++) {
            for (int i = 0; i < numberOfBooks; i++) {
                if (keyValuePairs[j].key == quantityArray[i])
                    indicesArray[i] = keyValuePairs[j].value;
            }
        }
            
        // The for loop below assigns a value to each element of the booksNew array in such a way that the array is sorted by quantity
        for (int i = 0; i < numberOfBooks; i++) {
            booksNew[i] = books[indicesArray[i]];
        }
        
        // The statement below prints the newly-created array
        cout << "Inventory sorted by quantity: " << endl;
        for (int i = 0; i < numberOfBooks; i++) {
            cout << booksNew[i] << endl;
        }
        
        // The following lines free memory that was dynamically allocated with the "new" keyword in the variable definitions above
        delete[] booksNew;
        delete[] quantityArray;
        delete[] indicesArray;
        delete[] keyValuePairs;
        
        // The following lines free make the variables nullpointers
        booksNew = nullptr;
        quantityArray = nullptr;
        indicesArray = nullptr;
        keyValuePairs = nullptr;
        
        // The statement below returns to the report module menu
        reportModule();
    }
    
    // This function prints the book in the inventory sorted by date added
    void printBooksSortedByDate() {
        
        // The statement below declares a variable that will hold the sorted array of books
        Book* booksNew = new Book[numberOfBooks];
        
        // The statement below declares a variable that will hold the date added of each book in the inventory
        int* dateArray = new int[numberOfBooks];
        
        // The statement below declares a variable that will hold the index of each book in the inventory
        int* indicesArray = new int[numberOfBooks];
        
        // The statement below declares a variable that will hold an array of KeyValuePair objects that store the index of each book and the corresponding date added.
        KeyValuePair<int>* keyValuePairs = new KeyValuePair<int>[numberOfBooks];
        
        // The for loop below fills the dateArray variable with the date of each book
        for (int i = 0; i < numberOfBooks; i++) {
            string date = books[i].getDateAdded();
            date.erase(removeFunction(date.begin(), date.end(), '\"' ),date.end());
            dateArray[i] = stoi(date);
        }

        // The for loop below fills the keyValuePairs variable with the date added and index of each book
        for (int i = 0; i < numberOfBooks; i++) {
            keyValuePairs[i].key = dateArray[i];
            keyValuePairs[i].value = i;
        }

        // The statement below sorts the dateArray variable
        selectionSort<int>(dateArray,numberOfBooks);

        // The for loop below assigns a value to each element of the indicesArray variable at location i that is equal to the index of the ith oldest book of the inventory
        for (int j = 0; j < numberOfBooks; j++) {
            for (int i = 0; i < numberOfBooks; i++) {
                if (keyValuePairs[j].key == dateArray[i])
                    indicesArray[i] = keyValuePairs[j].value;
            }
        }

        // The for loop below assigns a value to each element of the booksNew array in such a way that the array is sorted by date
        for (int i = 0; i < numberOfBooks; i++) {
            booksNew[i] = books[indicesArray[i]];
        }

        // The statement below prints the newly-created array
        cout << "Inventory sorted by date added: " << endl;
        for (int i = 0; i < numberOfBooks; i++) {
            cout << booksNew[i] << endl;
        }
        
        // The following lines free memory that was dynamically allocated with the "new" keyword in the variable definitions above
        delete[] booksNew;
        delete[] dateArray;
        delete[] indicesArray;
        delete[] keyValuePairs;
        
        // The following lines free make the variables nullpointers
        booksNew = nullptr;
        dateArray = nullptr;
        indicesArray = nullptr;
        keyValuePairs = nullptr;
        
        // The statement below returns to the report module menu
        reportModule();
    }
    
    // This function prints the books in the inventory sorted by wholesale cost
    void printBooksSortedByWholesaleCost() {
        
        // The statement below declares a variable that will hold the sorted array of books
        Book* booksNew = new Book[numberOfBooks];
        
        // The statement below declares a variable that will hold the wholesale cost of each book in the inventory
        double* wholesaleCostArray = new double[numberOfBooks];
        
        // The statement below declares a variable that will hold the index of each book in the inventory
        int* indicesArray = new int[numberOfBooks];
        
        // The statement below declares a variable that will hold an array of KeyValuePair objects that store the index of each book and the corresponding wholesale cost.
        KeyValuePair<double>* keyValuePairs = new KeyValuePair<double>[numberOfBooks];
        
        // The for loop below fills the wholesaleCostArray variable with the wholesale cost of each book
        for (int i = 0; i < numberOfBooks; i++) {
            wholesaleCostArray[i] = books[i].getWholesaleCost();
        }
        
        // The for loop below fills the keyValuePairs variable with the wholesale cost and index of each book
        for (int i = 0; i < numberOfBooks; i++) {
            keyValuePairs[i].key = wholesaleCostArray[i];
            keyValuePairs[i].value = i;
        }
        
        // The statement below sorts the wholesakeCostArray variable
        selectionSort<double>(wholesaleCostArray,numberOfBooks);
        
        // The statement below reverses the wholesakeCostArray variable
        reverse<double>(wholesaleCostArray,numberOfBooks);
        
        // The for loop below assigns a value to each element of the indicesArray variable at location i that is equal to the index of the ith most costly book of the inventory
        for (int j = 0; j < numberOfBooks; j++) {
            for (int i = 0; i < numberOfBooks; i++) {
                if (keyValuePairs[j].key == wholesaleCostArray[i]) {
                    indicesArray[i] = keyValuePairs[j].value;
                }
            }
        }
            
        // The for loop below assigns a value to each element of the booksNew array in such a way that the array is sorted by wholesale cost
        for (int i = 0; i < numberOfBooks; i++) {
            booksNew[i] = books[indicesArray[i]];
        }
        
        // The statement below prints the newly-created array
        cout << "Inventory sorted by wholesale cost: " << endl;
        for (int i = 0; i < numberOfBooks; i++) {
            cout << booksNew[i] << endl;
        }
        
        // The following lines free memory that was dynamically allocated with the "new" keyword in the variable definitions above
        delete[] booksNew;
        delete[] wholesaleCostArray;
        delete[] indicesArray;
        delete[] keyValuePairs;
        
        // The following lines free make the variables nullpointers
        booksNew = nullptr;
        wholesaleCostArray = nullptr;
        indicesArray = nullptr;
        keyValuePairs = nullptr;
        
        // The statement below returns to the report module menu
        reportModule();

    }
    
    // This function allows the user to change a book in the inventory
    void changeBook(string ISBN) {
        
        // The variable declared below will hold the book that will be changed by the user
        Book bookToChange;
        
        // The variable below keeps track of whether any book was found with the ISBN the user provided or not
        bool anyMatchedSearch = false;
        
        // The variable below keeps track of the index of the book that will be changed
        int bookIndex = 0;
        
        // The for loop below checks if any book has the ISBN entered by the user
        for (int i = 0; i < numberOfBooks; i++) {
            string bookISBN = books[i].getISBN();
            bookISBN.erase(removeFunction(bookISBN.begin(), bookISBN.end(), '\"' ),bookISBN.end());
            bookISBN.erase(removeFunction(bookISBN.begin(), bookISBN.end(), '\n' ),bookISBN.end());
            if (bookISBN == ISBN) {
                bookToChange = books[i];
                anyMatchedSearch = true;
                bookIndex = i;
            }
        }
        
        if (anyMatchedSearch) {
            string input;
            cout << "What do you want to change in the book?" << endl;
            cout << "a: ISBN" << endl;
            cout << "b: Title " << endl;
            cout << "c: Author" << endl;
            cout << "d: Publisher" << endl;
            cout << "e: Date added (must be in the format YYYYMMDD)" << endl;
            cout << "f: Quantity on hand" << endl;
            cout << "g: Wholesale cost" << endl;
            cout << "h: Retail price" << endl;
                cin >> input;
            
            if (input == "a") {
                string newISBN;
                cout << "Type the new ISBN" << endl;
                cin >> newISBN;
                books[bookIndex].setISBN(newISBN);
            } else if (input == "b") {
                string newTitle;
                cout << "Type the new title" << endl;
                cin.ignore();
                getline (cin,newTitle, '\n');
                books[bookIndex].setTitle(newTitle);
            } else if (input == "c") {
                string newAuthor;
                cout << "Type the new author" << endl;
                getline (cin,newAuthor, '\n');
                books[bookIndex].setAuthor(newAuthor);
            } else if (input == "d") {
                string newPublisher;
                cout << "Type the new publisher" << endl;
                getline (cin,newPublisher, '\n');
                books[bookIndex].setPublisher(newPublisher);
            } else if (input == "e") {
                string newDateAdded;
                cout << "Type the new date added" << endl;
                cin >> newDateAdded;
                books[bookIndex].setDateAdded(newDateAdded);
            } else if (input == "f") {
                string newQuantityOnHand;
                cout << "Type the new quantity on hand" << endl;
                cin >> newQuantityOnHand;
                try {
                    books[bookIndex].setQuantityOnHand(stoi(newQuantityOnHand));
                } catch (...) {
                    cout << "That is not a valid date" << endl;
                }
            } else if (input == "g") {
                string newWholesaleCost;
                cout << "Type the new wholesale cost" << endl;
                cin >> newWholesaleCost;
                try {
                    books[bookIndex].setWholesaleCost(stod(newWholesaleCost));
                    // The line below re-calculate the wholesale value of the inventory, since it changes if the wholesale value of a book changes.
                    wholesaleValue = inventoryWholesaleValue();
                } catch (...) {
                    cout << "That is not a valid cost" << endl;
                }
            } else if (input == "h") {
                string newRetailPrice;
                cout << "Type the new retail price" << endl;
                cin >> newRetailPrice;
                try {
                    books[bookIndex].setRetailPrice(stod(newRetailPrice));
                } catch (...) {
                    cout << "That is not a valid price" << endl;
                }
            }
            cout << "The book was successfully changed. " << endl;
            
        } else {
            cout << endl << "There is no book in the inventory with this ISBN." << endl << endl;
        }
        
        // The statement below returns to the inventory menu
        inventoryDatabaseModule();
    }
    
    // This function allows the user to add a book to the inventory
    void addBook() {
        
        int  quantityOnHand;
        string title, author, publisher, dateAdded, ISBN, wholesaleCostString, retailPriceString, quantityOnHandString;
        double wholesaleCost, retailPrice;
        
        cout << "Now enter the following information about the new book: \n";
        
        cout << "ISBN: \n";
        cin >> ISBN;
        
        cout << "Title: \n";
        cin.ignore();
        getline (cin,title, '\n');
        
        cout << "Author: \n";
        getline (cin,author, '\n');
        
        cout << "Publisher: \n";
        getline (cin,publisher, '\n');
        
        cout << "Date added (must be in the format YYYYMMDD): \n";
        getline (cin,dateAdded, '\n');
        
        cout << "Wholesale cost: \n";
        getline (cin,wholesaleCostString, '\n');
        try {
            wholesaleCost = stod(wholesaleCostString);
        } catch(...) {
            cout << "That is not a valid cost. Try changing the cost later." << endl;
            wholesaleCost = 0.0;
        }
        
        cout << "Retail price: \n";
        getline(cin,retailPriceString,'\n');
        try {
            retailPrice = stod(retailPriceString);
        } catch(...) {
            cout << "That is not a valid price. Try changing the price later." << endl;
            retailPrice = 0.0;
        }
        
        cout << "Quantity on hand: \n";
        getline(cin,quantityOnHandString,'\n');
        try {
            quantityOnHand = stoi(quantityOnHandString);
        } catch(...) {
            cout << "That is not a valid quantity. Try changing it later." << endl;
            quantityOnHand = 0;
        }
        
        
        Book newBook = Book(ISBN, wholesaleCost, retailPrice, quantityOnHand, title, author, publisher, dateAdded);
        
        numberOfBooks = numberOfBooks + 1;
            
        Book* booksNew = new Book[numberOfBooks];
        
        for (int i = 0; i < numberOfBooks; i++) {
            if ( i == (numberOfBooks - 1)) {
                booksNew[i] = newBook;
            } else {
                booksNew[i] = books[i];
            }
        }
        
        createBookArray(numberOfBooks);
        for (int i = 0; i < numberOfBooks; i++)
            setBook(booksNew[i], i);
        
        cout << "The book \"" << newBook.getTitle() << "\" was successfully added." << endl;
        
        // The following line frees memory that was dynamically allocated with the "new" keyword in the variable definition above
        delete[] booksNew;
        
        // The following line makes booksNew a nullpointer
        booksNew = nullptr;
        
        inventoryDatabaseModule();
    }

    // This function allows the user to remove a book in the inventory
    void removeBook(string ISBN) {
        
        // The variable below keeps track of whether any book was found with the ISBN the user provided or not
        bool anyMatchedSearch = false;
        
        // The for loop below checks whether there is any book in the inventory with the ISBN the user provided
        for (int i = 0; i < numberOfBooks; i++) {
            string bookISBN = books[i].getISBN();
            bookISBN.erase(removeFunction(bookISBN.begin(), bookISBN.end(), '\"' ),bookISBN.end());
            bookISBN.erase(removeFunction(bookISBN.begin(), bookISBN.end(), '\n' ),bookISBN.end());
            if (bookISBN == ISBN) {
                anyMatchedSearch = true;
            }
        }
        
        if (anyMatchedSearch) {
            
            numberOfBooks = numberOfBooks - 1;
                
            Book* booksNew = new Book[numberOfBooks];
            
            // This for loop fills out an array with all of the books in the inventory except the one that needs to be removed
            int j = 0;
            for (int i = 0; i < numberOfBooks; i++) {
                string bookISBN = books[i].getISBN();
                bookISBN.erase(removeFunction(bookISBN.begin(), bookISBN.end(), '\"' ),bookISBN.end());
                bookISBN.erase(removeFunction(bookISBN.begin(), bookISBN.end(), '\n' ),bookISBN.end());
                if ( bookISBN != ISBN) {
                    booksNew[i] = books[j];
                } else {
                    j++;
                    booksNew[i] = books[j];
                }
                j++;
            }
            
            // The line below assigns the value of "booksNew" to the inventory's "books" property
            createBookArray(numberOfBooks);
            for (int i = 0; i < numberOfBooks; i++)
                setBook(booksNew[i], i);
            
            // The following line frees memory that was dynamically allocated with the "new" keyword in the variable definition above
            delete[] booksNew;
            
            // The following line makes booksNew a nullpointer
            booksNew = nullptr;
            
            cout << "The book was successfully removed." << endl;
        } else {
            cout << "No book with this ISBN is in the inventory." << endl;
        }
        
        // The statement below returns to the inventory menu
        inventoryDatabaseModule();
        
    }
    // This function prints each book in the inventory (t is defined outside of the class)
    friend void printInventory(Inventory inventory);
    
    // This function prints the total wholesale value of the each book in the inventory as well as the total wholesale value of the whole inventory
    void printWholesaleValueOfInventory() {
        
        for (int i = 0; i < numberOfBooks; i++) {
            cout << "Title: " << books[i].getTitle() << endl << "Total wholesale value: $" << books[i].getWholesaleValue() << endl << endl;
        }
        cout << "Total wholesale value of inventory: $" << inventoryWholesaleValue() << endl;
        
        // The statement below returns to the report module menu
        reportModule();
        
    }

    // This function prints the total retail value of the each book in the inventory as well as the total wholesale value of the whole inventory
    void printRetailValueOfInventory() {
        
        for (int i = 0; i < numberOfBooks; i++) {
            cout << "Title: " << books[i].getTitle() << endl << "Total retail value: $" << books[i].getRetailValue() << endl << endl;
        }
        cout << "Total retail value of inventory: $" << inventoryRetailValue() << endl;
        
        // The statement below returns to the report module menu
        reportModule();
        
    }
    
} inventory;


// This function starts the cashier module
void cashierModule() {
    
    Book* booksThatMatchSearch = new Book[inventory.getNumberOfBooks()];
    Book bookToPurchase;
    
    // tax rate
    const double TAX_RATE = .09;
    string input;
    
    // boolean variable that tracks whether any book in the inventory matched the user's search
    bool anyMatchedSearch = false;
        
    // Prompt user to search for a book
    cout << endl << "Which book would you like to purchase? You can enter the title of the book (or part of it), the name of the author, or the ISBN. The search is case-sensitive." << endl;
    cin >> input;
    
    // This for loop iterates over the entire inventory and checks whether the title, author or ISBN of any book matches the user input. If it does, it adds the book to the array of books that match the search.
    for (int i = 0; i < inventory.getNumberOfBooks(); i++) {
        if (inventory.getBook(i).getTitle().find(input) != string::npos ||
            inventory.getBook(i).getAuthor().find(input) != string::npos ||
            inventory.getBook(i).getISBN().find(input) != string::npos) {
            Book inventoryBook = inventory.getBook(i);
            booksThatMatchSearch[i] = inventoryBook;
            anyMatchedSearch = true;
        }
    }
        
    if (anyMatchedSearch) {
    
        cout << "The following books match your search. Press the number that corresponds to the book you want in order to purchase it." << endl;
        
        string in;
        
        int index;
        // This for loop prints each book in the inventory that matches the user's search
        for (int i = 0; i < inventory.getNumberOfBooks(); i++) {
            if (booksThatMatchSearch[i].getTitle() != "") {
                cout << i << ": " << booksThatMatchSearch[i] << endl;
            }
        }
        
        cin >> in;
        try {
            index = stoi(in);
            bookToPurchase = booksThatMatchSearch[index];
            
            // This if statement checks if there is a positive number of copies of the requested book in the inventory
            if (bookToPurchase.getQuantityOnHand() <= 0) {
                cout << "Sorry, we've ran out of that book. " << endl;
            } else {
                // This for loop identifies the purchased book in the inventory and subtracts 1 from the quantity on hand.
                for (int i = 0; i < inventory.getNumberOfBooks(); i++) {
                    if (bookToPurchase.getISBN() == inventory.getBook(i).getISBN()) {
                        inventory.getBook(i).setQuantityOnHand(inventory.getBook(i).getQuantityOnHand() - 1);
                    }
                }
                // This statement creates a Sale object to execute the purchase of the book.
                Sale itemSale(bookToPurchase.getRetailPrice(), TAX_RATE);
                    
                // formating using iomanip library
                cout << fixed << showpoint << setprecision(2);
                
                //receipt headers
                cout << "Serendipity Book Sellers\n" << endl;
                
                //displaying  QTY, ISBN, Title, Price, Total HEADLINE
                cout << setw(5) << "QTY"<< setw(20) << "ISBN" << setw(60) << "Title" << setw(8) << "Price" << setw(8) << "Total" << endl;
                cout << "--------------------------------------------------------------------------------" << endl << endl;
                cout << endl;
                
                // call all the books added to cashier module
                
                //first line of the receipt
                cout << setw(5) << 1 << setw(20) << bookToPurchase.getISBN() << setw(60) << bookToPurchase.getTitle()
                         << "$" << setw(7) << bookToPurchase.getRetailPrice() << "$" << setw(8) << itemSale.getTotal() << endl;
                
                cout << endl << endl;
                
                // list of subtotal, total, and tax
                cout << right << " " << left << setw(20) << "Subtotal: $" << bookToPurchase.getRetailPrice() << endl;
                cout << right << " " << left << setw(20) << "Tax: $" << itemSale.getTax() << endl;
                cout << right << " " << left << setw(20) << "Total: $" << itemSale.getTotal() << endl;
                cout << endl;
                
                cout << "Thank you for shopping at Serendipity!\n";
                
            }

        } catch(...) {
            //Input was not an integer, so user must restart the search
            cout << "No books matched your search. You may search again." << endl;
        }
        
    } else {
        cout << "No books matched your search. You may search again." << endl;
    }
    
    delete[] booksThatMatchSearch;
    
    mainMenu();
    return;
    
}

// The lines below specify the function printInventory, which is a friend function of the Inventory class
void printInventory(Inventory inventory) {
    for (int i = 0; i < inventory.numberOfBooks; i++) {
        cout << inventory.books[i] << endl;
    }
    // The statement below returns to the report module menu
    reportModule();
}

// This function displays the menu of the inventory database module menu
void inventoryDatabaseModule() {
    
    // The variable declared below will be used to store user input
    string input;
    
    // The statements below present the user with the inventory database module menu
    cout << endl << "Which of the following things do you want to do?" << endl;
    cout << "a: Add a book" << endl;
    cout << "b: Remove a book" << endl;
    cout << "c: Edit a book's record" << endl;
    cout << "[You can press any other key, and then press \"Enter,\"  in order to exit this menu]" << endl;
        cin >> input;
    
    // These if/else statements calls the function the user wants to call
    if (input == "a")
        inventory.addBook();
    
    else if (input == "b") {
        string ISBN;
        cout << "Enter the ISBN of the book you want to remove: \n";
        cin >> ISBN;
        inventory.removeBook(ISBN);
    } else if (input == "c") {
        string ISBN;
        cout << "Enter the ISBN of the book you want to change: \n";
        cin >> ISBN;
        inventory.changeBook(ISBN);
    } else {
        mainMenu();
        return;
    }
    
}

// This function displays the menu of the report module
void reportModule() {
    
    string input;
    cout << endl << "Which of the following reports do you want to see?" << endl;
    cout << "a: Inventory List" << endl;
    cout << "b: Inventory Wholesale Value" << endl;
    cout << "c: Inventory Retail Value" << endl;
    cout << "d: Inventory books sorted by quantity (from greater to lesser)" << endl;
    cout << "e: Inventory books sorted by wholesale cost (from highest to lowest)" << endl;
    cout << "f: Inventory books sorted by age (from oldest to newest)" << endl;
    cout << "[You can press any other key, and then press \"Enter,\"  in order to exit this menu]" << endl;
        cin >> input;
        
    if (input == "a")
        printInventory(inventory);
    if (input == "b")
        inventory.printWholesaleValueOfInventory();
    if (input == "c")
        inventory.printRetailValueOfInventory();
    if (input == "d")
        inventory.printBooksSortedByQuantity();
    if (input == "e")
        inventory.printBooksSortedByWholesaleCost();
    if (input == "f")
        inventory.printBooksSortedByDate();
    else {
        mainMenu();
        return;
    }
    
}

// This function displays the main menu of the application
void mainMenu() {
    
    string in;
    
    cout << endl << "Welcome to Serendipity Booksellers's point-of-sale software package. Which module do you want to use?" << endl;
    cout << "a: Cashier module" << endl;
    cout << "b: Inventory Database module" << endl;
    cout << "c: Report module" << endl;
    cout << "x: Exit the program" << endl;
        cin >> in;
        
    // These if/else statements call the module that the user wants to call
    if (in == "a") {
        cashierModule();
    } else if (in == "b") {
        inventoryDatabaseModule();
    } else if (in == "c") {
        reportModule();
    } else if (in == "x") {
        return;
    } else {
        return;
    }
    
}

int main() {
    
    // The line below declares a variable to store the books that are in the input file
    Book* books = new Book[SIZE];
    // The line below sets the number of books of the inventory to be equal to 50, the value of the SIZE constant
    inventory.setNumberOfBooks(SIZE);

    // The variable declared below holds the path of the input file, which will be provided by the user
    string file;
    
    // The variable below will be used in the future to store the stream of the input file
    fstream dataInfile;
    
    // The line below prompts the user to enter the path of the input file
    cout << "Enter a file to read from: \n";
    cin >> file;

    // The line below attempts to open the input file
    dataInfile.open(file);

    // The line below checks if the file was opened successfully
    if (dataInfile.is_open()) {
        cout << "File has opened successfully\n";
        cout << endl;

        //processing....
        //setting values of book array
        for (int i = 0; i < SIZE; i++) {
            dataInfile >> books[i];
        }
    }
    else {
        //file error message
        cout << "File has failed to open\n";
    }
    
    // The statement below closes the input file
    dataInfile.close();
    
    // These statements assign the value of the array "books" to the "books" member of the inventory object
    inventory.createBookArray(SIZE);
    for (int i = 0; i < SIZE; i++)
        inventory.setBook(books[i], i);
    
    // The lines below calculate the total retail value and total wholesale value of the inventory and store the values to the appropriate variables
    inventory.setRetailValue(inventory.inventoryRetailValue());
    inventory.setWholesaleValue(inventory.inventoryWholesaleValue());
    
    // The following lines free memory that was dynamically allocated with the "new" keyword in the variable definitions above
    delete[] books;
    
    // The following line makes books a nullpointer
    books = nullptr;
    
    // The statement below calls the main menu
    mainMenu();
    
    // The following lines of code are meant to provide a substitution for system("pause").
    cout << endl << "Press enter to quit the program.";
    cin.ignore();
    while (cin.get() != '\n')
        cout << "Press enter to quit the program.";
    return 0;
}
