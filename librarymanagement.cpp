#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> // For sorting

using namespace std;

// Structure to store book details
struct Book {
    string book_id;
    string title;
    string author;
    int quantity;

    // Function to convert book details to a string for saving to file
    string to_string() const {
        return book_id + "," + title + "," + author + "," + std::to_string(quantity);
    }
};

// Class to manage the library
class Library {
private:
    vector<Book> books;

public:
    // Function to add a new book
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book '" << book.title << "' added to inventory." << endl;
    }

    // Function to remove a book by ID
    void removeBook(const string& book_id) {
        auto it = remove_if(books.begin(), books.end(),
                            [&book_id](const Book& book) { return book.book_id == book_id; });
        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book with ID '" << book_id << "' removed from inventory." << endl;
        } else {
            cout << "Book with ID '" << book_id << "' not found." << endl;
        }
    }

    // Function to search for a book by ID or title
    vector<Book> searchBook(const string& search_term) {
        vector<Book> results;
        for (const auto& book : books) {
            if (book.book_id == search_term || book.title == search_term) {
                results.push_back(book);
            }
        }
        return results;
    }

    // Function to display all available books
    void displayBooks() {
        if (books.empty()) {
            cout << "No books available in the inventory." << endl;
            return;
        }
        cout << "\nAvailable Books:" << endl;
        for (const auto& book : books) {
            cout << "ID: " << book.book_id << ", Title: " << book.title
                 << ", Author: " << book.author << ", Quantity: " << book.quantity << endl;
        }
    }

    // Function to display books sorted by title
    void displayBooksSorted() {
        if (books.empty()) {
            cout << "No books available to sort." << endl;
            return;
        }

        vector<Book> sorted_books = books;
        sort(sorted_books.begin(), sorted_books.end(),
             [](const Book& a, const Book& b) { return a.title < b.title; });

        cout << "\nBooks Sorted by Title:" << endl;
        for (const auto& book : sorted_books) {
            cout << "ID: " << book.book_id << ", Title: " << book.title
                 << ", Author: " << book.author << ", Quantity: " << book.quantity << endl;
        }
    }

    // Function to update the quantity of a book
    void updateQuantity(const string& book_id, int new_quantity) {
        for (auto& book : books) {
            if (book.book_id == book_id) {
                book.quantity = new_quantity;
                cout << "Quantity updated for book '" << book.title << "'." << endl;
                return;
            }
        }
        cout << "Book with ID '" << book_id << "' not found." << endl;
    }

    // Function to save the inventory to a file
    void saveInventory() {
        ofstream file("inventory.txt");
        for (const auto& book : books) {
            file << book.to_string() << endl;
        }
        file.close();
        cout << "Inventory saved to 'inventory.txt'." << endl;
    }

    // Function to load the inventory from a file
    void loadInventory() {
        ifstream file("inventory.txt");
        if (!file) {
            cout << "No previous inventory found. Starting with an empty library." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Book book;
            string quantity_str;
            getline(ss, book.book_id, ',');
            getline(ss, book.title, ',');
            getline(ss, book.author, ',');
            getline(ss, quantity_str, ',');
            book.quantity = stoi(quantity_str);
            books.push_back(book);
        }
        file.close();
        cout << "Inventory loaded from 'inventory.txt'." << endl;
    }
};

// User interface for the Library Management System
void mainMenu() {
    Library library;
    library.loadInventory();

    while (true) {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add a new book" << endl;
        cout << "2. Remove a book" << endl;
        cout << "3. Search for a book" << endl;
        cout << "4. Display all books" << endl;
        cout << "5. Display books sorted by title" << endl;
        cout << "6. Update book quantity" << endl;
        cout << "7. Save inventory" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        if (choice == 1) {
            Book new_book;
            cout << "Enter Book ID: ";
            getline(cin, new_book.book_id);
            cout << "Enter Book Title: ";
            getline(cin, new_book.title);
            cout << "Enter Book Author: ";
            getline(cin, new_book.author);
            cout << "Enter Book Quantity: ";
            cin >> new_book.quantity;
            cin.ignore(); // Clear the newline character from the input buffer
            library.addBook(new_book);
        } else if (choice == 2) {
            string book_id;
            cout << "Enter Book ID to remove: ";
            getline(cin, book_id);
            library.removeBook(book_id);
        } else if (choice == 3) {
            string search_term;
            cout << "Enter Book ID or Title to search: ";
            getline(cin, search_term);
            vector<Book> results = library.searchBook(search_term);
            if (!results.empty()) {
                cout << "\nSearch Results:" << endl;
                for (const auto& book : results) {
                    cout << "ID: " << book.book_id << ", Title: " << book.title
                         << ", Author: " << book.author << ", Quantity: " << book.quantity << endl;
                }
            } else {
                cout << "No books found." << endl;
            }
        } else if (choice == 4) {
            library.displayBooks();
        } else if (choice == 5) {
            library.displayBooksSorted();
        } else if (choice == 6) {
            string book_id;
            int new_quantity;
            cout << "Enter Book ID to update: ";
            getline(cin, book_id);
            cout << "Enter new quantity: ";
            cin >> new_quantity;
            cin.ignore(); // Clear the newline character from the input buffer
            library.updateQuantity(book_id, new_quantity);
        } else if (choice == 7) {
            library.saveInventory();
        } else if (choice == 8) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// Main function
int main() {
    mainMenu();
    return 0;
}