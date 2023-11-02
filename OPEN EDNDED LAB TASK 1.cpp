#include <iostream>
using namespace std;

class Book {
public:
    Book(const string& title) : title(title), isBorrowed(false), dueDate(0) {}

    bool isAvailable() const {
        return !isBorrowed;
    }

    void borrowBook(int days) {
        isBorrowed = true;
        dueDate = time(0) + days * 24 * 60 * 60;
    }

    void returnBook() {
        isBorrowed = false;
        dueDate = 0;
    }

    bool isLate() const {
        return isBorrowed && time(0) > dueDate;
    }

    const string& getTitle() const {
        return title;
    }

private:
    string title;
    bool isBorrowed;
    time_t dueDate;
};

class Library {
public:
    void addBook(const string& title) {
        books[title] = Book(title);
    }

    void borrowBook(const string& title, int days) {
        if (books.find(title) != books.end()) {
            Book& book = books[title];
            if (book.isAvailable()) {
                book.borrowBook(days);
                cout << "Borrowed '" << title << "' for " << days << " days." << endl;
            }
            else {
                cout << "The book '" << title << "' is already borrowed." << endl;
            }
        }
        else {
            cout << "Book not found in the library." << endl;
        }
    }

    void returnBook(const string& title) {
        if (books.find(title) != books.end()) {
            Book& book = books[title];
            if (book.isLate()) {
                int daysLate = (time(0) - book.dueDate) / (24 * 60 * 60);
                int fine = daysLate * 1;
                cout << "Returned '" << title << "' " << daysLate << " days late. You owe $" << fine << " in fines." << endl;
            }
            else {
                cout << "Returned '" << title << "' on time. No fines incurred." << endl;
            }
            book.returnBook();
        }
        else {
            cout << "Book not found in the library." << endl;
        }
    }

private:
    map<string, Book> books;
};

int main() {
    Library library;

    library.addBook("Book 1");
    library.addBook("Book 2");

    library.borrowBook("Book 1", 10);
    library.borrowBook("Book 2", 20);

    library.returnBook("Book 1");
    library.returnBook("Book 2");

    return 0;
}
