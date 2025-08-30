#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    int year;
    bool available;

public:
    
    Book() {
        id = 0;
        title = "";
        author = "";
        year = 0;
        available = false;
    }

   
    Book(int _id, const string& _title, const string& _author, int _year, bool _available) {
        id = _id;
        title = _title;
        author = _author;
        year = _year;
        available = _available;
    }

   
    int getId() const {
        return id; }

    string getTitle() const { 
        return title; }

    string getAuthor() const {
        return author; }

    int getYear() const {
        return year; }

    bool isAvailable() const {
        return available; }

    void setId(int _id) { 
        id = _id; }


    void setTitle(const string& _title) { 
        
        title = _title; }


    void setAuthor(const string& _author) { 
        
        author = _author; }


    void setYear(int _year) { 
        
        year = _year; }


    void setAvailable(bool _available) { 
        
        available = _available; }

    
    void borrowBook() {


        if (available == true) {
            available = false;
        }
    }

    
    void returnBook() {
        if (available == false) {
            available = true;
        }
    }

    
    void display() const {
        cout << "ID: " << id << "\n";
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "Year: " << year << "\n";
        cout << "Status: " << (available ? "Available" : "Borrowed") << "\n";
    }
};


const int CAPACITY = 100;

void showHeader() {
    cout << "*************** Welcome to the Library ***************\n";
    cout << "Please choose one of the following operations:\n\n";
    cout << "1 - Add a new book\n";
    cout << "2 - Borrow a book\n";
    cout << "3 - Return a book\n";
    cout << "4 - Display details of a book (by ID)\n";
    cout << "5 - List all available books\n";
    cout << "0 - Exit\n\n";
}

void pauseForMenu() {
    cout << "Press Enter key to return to Main Menu!";
    cin.ignore(10000, '\n'); 
    cin.get();               
    cout << "\n";
}


int generateUniqueId(Book library[], int count) {
    int newId;
    bool unique = false;
    while (!unique) {
        newId = 10000 + rand() % 90000; 
        unique = true;
        for (int i = 0; i < count; i++) {
            if (library[i].getId() == newId) {
                unique = false;
                break;
            }
        }
    }
    return newId;
}


int findIndexById(Book library[], int count, int targetId) {
    for (int i = 0; i < count; i++) {
        if (library[i].getId() == targetId) {
            return i;
        }
    }
    return -1;
}


void addNewBook(Book library[], int& count) {
    if (count >= CAPACITY) {
        cout << "Library is full. Cannot add more books.\n";
        pauseForMenu();
        return;
    }

    string t, a;
    int y;

    cout << "Enter title: ";
    cin.ignore();              
    getline(cin, t);

    cout << "Enter author: ";
    getline(cin, a);

    cout << "Enter year: ";
    cin >> y;

    int newId = generateUniqueId(library, count);
    Book b(newId, t, a, y, true);
    library[count] = b;
    count++;

    cout << "\nBook added successfully!\n";
    cout << "Title: " << t << "\n";
    cout << "ID: " << newId << "\n\n";
    pauseForMenu();
}


void borrowBookById(Book library[], int count) {
    int bid;
    cout << "Enter Book ID: ";
    cin >> bid;

    int idx = findIndexById(library, count, bid);
    if (idx == -1) {
        cout << "Book not found.\n\n";
        pauseForMenu();
        return;
    }

    if (library[idx].isAvailable() == true) {
        library[idx].borrowBook();
        cout << "You have successfully borrowed '" << library[idx].getTitle() << "'.\n\n";
    }
    else {
        cout << "This book is not available.\n\n";
    }
    pauseForMenu();
}


void returnBookById(Book library[], int count) {
    int bid;
    cout << "Enter Book ID: ";
    cin >> bid;

    int idx = findIndexById(library, count, bid);
    if (idx == -1) {
        cout << "Book not found.\n\n";
        pauseForMenu();
        return;
    }

    if (library[idx].isAvailable() == false) {
        library[idx].returnBook();
        cout << "You have successfully returned '" << library[idx].getTitle() << "'.\n\n";
    }
    else {
        cout << "Book was not borrowed.\n\n";
    }
    pauseForMenu();
}


void displayBookDetails(Book library[], int count) {
    int bid;
    cout << "Enter Book ID: ";
    cin >> bid;

    int idx = findIndexById(library, count, bid);
    if (idx == -1) {
        cout << "Book not found.\n\n";
    }
    else {
        cout << "\n";
        library[idx].display();
        cout << "\n";
    }
    pauseForMenu();
}


void listAllAvailable(Book library[], int count) {
    bool any = false;
    cout << "Available Books:\n";
    for (int i = 0; i < count; i++) {
        if (library[i].isAvailable() == true) {
            any = true;
            cout << "ID: " << library[i].getId()
                << " | Title: " << library[i].getTitle()
                << " | Author: " << library[i].getAuthor()
                << " | Year: " << library[i].getYear() << "\n";
        }
    }
    if (any == false) {
        cout << "No books available at the moment.\n";
    }
    cout << "\n";
    pauseForMenu();
}

int main() {
    
    cout << fixed << showpoint << setprecision(2);

    srand(static_cast<unsigned int>(time(0)));

    Book library[CAPACITY];
    int count = 0;

    while (true) {
        showHeader();
        cout << "Choice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n\n";
            continue;
        }

        if (choice == 1) {
            addNewBook(library, count);
        }
        else if (choice == 2) {
            borrowBookById(library, count);
        }
        else if (choice == 3) {
            returnBookById(library, count);
        }
        else if (choice == 4) {
            displayBookDetails(library, count);
        }
        else if (choice == 5) {
            listAllAvailable(library, count);
        }
        else if (choice == 0) {
            cout << "Thank you for using the Library System! Goodbye!\n";
            break;
        }
        else {
            cout << "Please choose a valid option.\n\n";
        }
    }
    return 0;
}
