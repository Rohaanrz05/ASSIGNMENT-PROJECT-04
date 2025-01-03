#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Structure to store product details
sir wajid
struct Product {
    int id;
    string name;
    string category;
    double price;
    int stock;

    void display() const {
        cout << left << setw(10) << id << setw(20) << name
             << setw(15) << category << setw(10) << price
             << setw(10) << stock << endl;
    }
};

// Structure to store sales data
struct Sale {
    int productId;
    string productName;
    int quantity;
    double totalAmount;
};

// Global vectors for products and sales
vector<Product> products;
vector<Sale> sales;

// Function to load products from a file
void loadProducts() {
    ifstream file("products.txt");
    if (file.is_open()) {
        Product p;
        while (file >> p.id >> p.name >> p.category >> p.price >> p.stock) {
            products.push_back(p);
        }
        file.close();
    }
}

// Function to save products to a file
void saveProducts() {
    ofstream file("products.txt");
    for (const auto& p : products) {
        file << p.id << " " << p.name << " " << p.category << " "
             << p.price << " " << p.stock << endl;
    }
    file.close();
}

// Function to display available products
void viewProducts() {
    cout << left << setw(10) << "ID" << setw(20) << "Name"
         << setw(15) << "Category" << setw(10) << "Price"
         << setw(10) << "Stock" << endl;
    for (const auto& p : products) {
        p.display();
    }
}

// Function to search for products by ID or Category
void searchProducts() {
    cout << "Search by: 1. ID  2. Category\nChoose an option: ";
    int option;
    cin >> option;
    if (option == 1) {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;
        for (const auto& p : products) {
            if (p.id == id) {
                p.display();
                return;
            }
        }
        cout << "Product not found.\n";
    } else if (option == 2) {
        string category;
        cout << "Enter Category: ";
        cin >> category;
        for (const auto& p : products) {
            if (p.category == category) {
                p.display();
            }
        }
    } else {
        cout << "Invalid option.\n";
    }
}

// Function to add a product to the cart ....
void addToCart(vector<Product*>& cart) {
    int id, quantity;
    cout << "Enter Product ID: ";
    cin >> id;
    cout << "Enter Quantity: ";
    cin >> quantity;
    for (auto& p : products) {
        if (p.id == id && p.stock >= quantity) {
            p.stock -= quantity;
            cart.push_back(&p);
            cout << "Added to cart.\n";
            return;
        }
    }
    cout << "Product not available or insufficient stock.\n";
}

// Function to checkout
void checkout(vector<Product*>& cart) {
    double total = 0;
    cout << "Bill:\n";
    for (auto* p : cart) {
        double amount = p->price;
        total += amount;
        sales.push_back({p->id, p->name, 1, amount});
        cout << p->name << " - " << p->price << endl;
    }
    cout << "Total: " << total << endl;
    cart.clear();
    saveProducts();  // Save updated stock
}

// Admin functionalities
void adminMenu() {
    while (true) {
        cout << "Admin Menu:\n1. Add Product\n2. Update Product\n3. Delete Product\n4. View Sales\n5. Exit\nChoose an option: ";
        int option;
        cin >> option;
        if (option == 1) {
            Product p;
            cout << "Enter Product Details (ID Name Category Price Stock): ";
            cin >> p.id >> p.name >> p.category >> p.price >> p.stock;
            products.push_back(p);
            saveProducts();
        } else if (option == 2) {
            int id;
            cout << "Enter Product ID to Update: ";
            cin >> id;
            for (auto& p : products) {
                if (p.id == id) {
                    cout << "Enter New Details (Name Category Price Stock): ";
                    cin >> p.name >> p.category >> p.price >> p.stock;
                    saveProducts();
                }s
            }
        } else if (option == 3) {
            int id;
            cout << "Enter Product ID to Delete: ";
            cin >> id;
            products.erase(remove_if(products.begin(), products.end(),
                                     [id](const Product& p) { return p.id == id; }),
                           products.end());
            saveProducts();
        } else if (option == 4) {
            for (const auto& sale : sales) {
                cout << "Product ID: " << sale.productId << ", Product Name: " << sale.productName
                     << ", Quantity: " << sale.quantity << ", Total Amount: " << sale.totalAmount << endl;
            }
        } else if (option == 5) {
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
}

// Main function
int main() {
    loadProducts();
    while (true) {
        cout << "1. View Products\n2. Search Products\n3. Add to Cart\n4. Checkout\n5. Admin\n6. Exit\nChoose an option: ";
        int choice;
        cin >> choice;
        vector<Product*> cart;
        switch (choice) {
            case 1:
                viewProducts();
                break;
            case 2:
                searchProducts();
                break;
            case 3:
                addToCart(cart);
                break;
            case 4:
                checkout(cart);
                break;
            case 5:
                adminMenu();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
                \\ sir wajid the great
        }
    }
}
