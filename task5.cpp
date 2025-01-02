#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>  // For remove_if
#include <cstdlib>

using namespace std;

// Structure to store product details
struct Product {
    int productID;
    string name;
    string category;
    double price;
    int stockQuantity;
};

// Structure to store sales transaction
struct Sale {
    int productID;
    int quantity;
    double totalAmount;
};

// Global variables
vector<Product> products;
vector<Sale> sales;

// Function to load products from a file
void loadProducts() {
    ifstream inFile("products.txt");
    if (inFile.is_open()) {
        Product p;
        while (inFile >> p.productID) {
            inFile.ignore();  // Ignore the newline after reading productID
            getline(inFile, p.name);
            getline(inFile, p.category);
            inFile >> p.price >> p.stockQuantity;
            products.push_back(p);
        }
        inFile.close();
    } else {
        cout << "Error loading products." << endl;
    }
}

// Function to save products to a file
void saveProducts() {
    ofstream outFile("products.txt");
    if (outFile.is_open()) {
        for (auto& p : products) {
            outFile << p.productID << endl;
            outFile << p.name << endl;
            outFile << p.category << endl;
            outFile << p.price << endl;
            outFile << p.stockQuantity << endl;
        }
        outFile.close();
    } else {
        cout << "Error saving products." << endl;
    }
}

// Function to load sales data from a file
void loadSales() {
    ifstream inFile("sales.txt");
    if (inFile.is_open()) {
        Sale s;
        while (inFile >> s.productID >> s.quantity >> s.totalAmount) {
            sales.push_back(s);
        }
        inFile.close();
    } else {
        cout << "Error loading sales data." << endl;
    }
}

// Function to save sales data to a file
void saveSales() {
    ofstream outFile("sales.txt");
    if (outFile.is_open()) {
        for (auto& s : sales) {
            outFile << s.productID << " " << s.quantity << " " << s.totalAmount << endl;
        }
        outFile.close();
    } else {
        cout << "Error saving sales data." << endl;
    }
}

// Function to display all products
void displayProducts() {
    cout << "ID\tName\tCategory\tPrice\tStock\n";
    for (auto& p : products) {
        cout << p.productID << "\t" << p.name << "\t" << p.category << "\t" << p.price << "\t" << p.stockQuantity << endl;
    }
}

// Function to search a product by ID
void searchProductByID() {
    int id;
    cout << "Enter product ID to search: ";
    cin >> id;
    bool found = false;
    for (auto& p : products) {
        if (p.productID == id) {
            cout << "Product found: " << p.name << ", " << p.category << ", " << p.price << ", Stock: " << p.stockQuantity << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Product not found." << endl;
    }
}

// Function to search products by category
void searchProductByCategory() {
    string category;
    cout << "Enter product category to search: ";
    cin >> ws;  // clear the buffer
    getline(cin, category);
    bool found = false;
    for (auto& p : products) {
        if (p.category == category) {
            cout << "Product found: " << p.name << ", " << p.category << ", " << p.price << ", Stock: " << p.stockQuantity << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No products found in this category." << endl;
    }
}

// Function to add a product to the cart
void addProductToCart(vector<Product>& cart) {
    int id, qty;
    cout << "Enter product ID: ";
    cin >> id;
    cout << "Enter quantity: ";
    cin >> qty;

    for (auto& p : products) {
        if (p.productID == id && p.stockQuantity >= qty) {
            Product cartProduct = p;
            cartProduct.stockQuantity = qty;
            cart.push_back(cartProduct);
            p.stockQuantity -= qty;  // Update stock
            cout << "Product added to cart!" << endl;
            return;
        }
    }
    cout << "Insufficient stock or invalid product ID." << endl;
}

// Function to checkout and generate bill
void checkout(vector<Product>& cart) {
    double totalBill = 0;
    for (auto& p : cart) {
        totalBill += p.price * p.stockQuantity;
        Sale s = {p.productID, p.stockQuantity, p.price * p.stockQuantity};
        sales.push_back(s);
    }

    cout << "Your total bill: " << totalBill << endl;
    saveSales();
    cart.clear();  // Clear cart after checkout
    saveProducts();  // Save updated stock data
}

// Admin functions
void addProduct() {
    Product p;
    cout << "Enter product details:" << endl;
    cout << "ID: ";
    cin >> p.productID;
    cout << "Name: ";
    cin >> ws;  // clear buffer
    getline(cin, p.name);
    cout << "Category: ";
    getline(cin, p.category);
    cout << "Price: ";
    cin >> p.price;
    cout << "Stock Quantity: ";
    cin >> p.stockQuantity;

    products.push_back(p);
    saveProducts();
    cout << "Product added successfully!" << endl;
}

void updateProduct() {
    int id;
    cout << "Enter product ID to update: ";
    cin >> id;

    for (auto& p : products) {
        if (p.productID == id) {
            cout << "Enter new details for product " << p.name << ":" << endl;
            cout << "Name: ";
            cin >> ws;
            getline(cin, p.name);
            cout << "Category: ";
            getline(cin, p.category);
            cout << "Price: ";
            cin >> p.price;
            cout << "Stock Quantity: ";
            cin >> p.stockQuantity;

            saveProducts();
            cout << "Product updated successfully!" << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

void deleteProduct() {
    int id;
    cout << "Enter product ID to delete: ";
    cin >> id;

    auto it = remove_if(products.begin(), products.end(), [id](Product& p) { return p.productID == id; });
    if (it != products.end()) {
        products.erase(it, products.end());
        saveProducts();
        cout << "Product deleted successfully!" << endl;
    } else {
        cout << "Product not found." << endl;
    }
}

void viewSalesReport() {
    cout << "Sales Report:\n";
    for (auto& s : sales) {
        cout << "Product ID: " << s.productID << ", Quantity: " << s.quantity << ", Total: " << s.totalAmount << endl;
    }
}

// Admin menu
void adminMenu() {
    int choice;
    do {
        cout << "Admin Menu:\n";
        cout << "1. Add Product\n2. Update Product\n3. Delete Product\n4. View Sales Report\n5. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addProduct(); break;
            case 2: updateProduct(); break;
            case 3: deleteProduct(); break;
            case 4: viewSalesReport(); break;
            case 5: cout << "Exiting Admin Menu.\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 5);
}

// User menu
void userMenu() {
    vector<Product> cart;
    int choice;
    do {
        cout << "User Menu:\n";
        cout << "1. View Products\n2. Search by ID\n3. Search by Category\n4. Add to Cart\n5. Checkout\n6. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: displayProducts(); break;
            case 2: searchProductByID(); break;
            case 3: searchProductByCategory(); break;
            case 4: addProductToCart(cart); break;
            case 5: checkout(cart); break;
            case 6: cout << "Exiting User Menu.\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 6);
}

int main() {
    loadProducts();
    loadSales();

    int choice;
    do {
        cout << "1. Admin Mode\n2. User Mode\n3. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: adminMenu(); break;
            case 2: userMenu(); break;
            case 3: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 3);
    return 0;
}
