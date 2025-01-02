#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Structure to store book details


struct Book {
    string book_id;
    string title;
    string author;
    int quantity;
};

// Function prototypes
void addBook(vector<Book>& books);
void removeBook(vector<Book>& books, const string& book_id);
void searchBook(const vector<Book>& books, const string& search_term);
void displayBooks(const vector<Book>& books);
void saveInventory(const vector<Book>& books);
void loadInventory(vector<Book>& books);
void updateQuantity(vector<Book>& books, const string& book_id, int new_quantity);

int main() {
    vector<Book> books;
    loadInventory(books);

    while (true) {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add a new book" << endl;
        cout << "2. Remove a book" << endl;
        cout << "3. Search for a book" << endl;
        cout << "4. Display all books" << endl;
        cout << "5. Update book quantity" << endl;
        cout << "6. Save inventory" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        if (choice == 1) 
        {
            addBook(books);
        } 
            else if (choice == 2) 
        {
            string book_id;
            cout << "Enter Book ID to remove: ";
            getline(cin, book_id);
            removeBook(books, book_id);
        } 
            else if (choice == 3) 
        {
            string search_term;
            cout << "Enter Book ID or Title to search: ";
            getline(cin, search_term);
            searchBook(books, search_term);
        } 
            else if (choice == 4) {
            displayBooks(books);
        }  
            else if (choice == 5) {
            string book_id;
            int new_quantity;
            cout << "Enter Book ID to update: ";
            getline(cin, book_id);
            cout << "Enter new quantity: ";
            cin >> new_quantity;
            cin.ignore(); // Clear the newline character from the input buffer
            updateQuantity(books, book_id, new_quantity);
        } 
            else if (choice == 6) 
        {
            saveInventory(books);
        } 
            else if (choice == 7) 
        {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
            else 
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

void addBook(vector<Book>& books) 
{
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
    books.push_back(new_book);
    cout << "Book '" << new_book.title << "' added to inventory." << endl;
}

void removeBook(vector<Book>& books, const string& book_id) 
{
    for (auto it = books.begin(); it != books.end(); ++it) 
    {
        if (it->book_id == book_id) 
        {
            books.erase(it);
            cout << "Book with ID '" << book_id << "' removed from inventory." << endl;
            return;
        }
    }
    cout << "Book with ID '" << book_id << "' not found." << endl;
}

void searchBook(const vector<Book>& books, const string& search_term) {
    for (const auto& book : books) {
        if (book.book_id == search_term || book.title == search_term) {
            cout << "ID: " << book.book_id << ", Title: " << book.title
                 << ", Author: " << book.author << ", Quantity: " << book.quantity << endl;
            return;
        }
    }
    cout << "No books found." << endl;
}

void displayBooks(const vector<Book>& books) 
{
    if (books.empty()) 
    {
        cout << "No books available in the inventory." << endl;
        return;
    }
    cout << "\nAvailable Books:" << endl;
    for (const auto& book : books) {
        cout << "ID: " << book.book_id << ", Title: " << book.title
             << ", Author: " << book.author << ", Quantity: " << book.quantity << endl;
    }
}

void saveInventory(const vector<Book>& books) {
    ofstream file("inventory.txt");
    if (!file) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    for (const auto& book : books) {
        file << book.book_id << "," << book.title << "," << book.author << "," << book.quantity << endl;
    }
    file.close();
    cout << "Inventory saved to 'inventory.txt'." << endl;
}

void loadInventory(vector<Book>& books) 
{
    ifstream file("inventory.txt");
    if (!file) 
    {
        cout << "No previous inventory found. Starting with an empty library." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        Book book;
        stringstream ss(line);
        getline(ss, book.book_id, ',');
        getline(ss, book.title, ',');
        getline(ss, book.author, ',');
        ss >> book.quantity;
        books.push_back(book);
    }
    file.close();
    cout << "Inventory loaded from 'inventory.txt'." << endl;
}

void updateQuantity(vector<Book>& books, const string& book_id, int new_quantity) 
{
    for (auto& book : books) 
    {
        if (book.book_id == book_id) 
        {
            book.quantity = new_quantity;
            cout << "Quantity updated for book '" << book.title << "'." << endl;
            return;
        }
    }
    cout << "Book with ID '" << book_id << "' not found." << endl;
}

