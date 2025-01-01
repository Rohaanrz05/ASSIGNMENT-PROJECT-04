#include <iostream>

#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm> // For sorting
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#

using namespace std;

// Structure to store menu item details
struct MenuItem {
    string item_code;
    string name;
    double price;
    int quantity_available;

    // Function to convert menu item details to a string for saving to file
    string to_string() const {
        return item_code + "," + name + "," + std::to_string(price) + "," + std::to_string(quantity_available);
    }
};

// Class to manage the restaurant menu and orders
class Restaurant {
private:
    vector<MenuItem> menu;
    map<string, int> order_summary; // To store the summary of all orders

public:
    // Function to load menu from a file
    void loadMenu() {
        ifstream file("menu.txt");
        if (!file) {
            cout << "No previous menu found. Starting with an empty menu." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            MenuItem item;
            string price_str, quantity_str;
            size_t pos = 0;
            pos = line.find(',');
            item.item_code = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            item.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            item.price = stod(line.substr(0, pos));
            line.erase(0, pos + 1);
            item.quantity_available = stoi(line);
            menu.push_back(item);
        }
        file.close();
        cout << "Menu loaded from 'menu.txt'." << endl;
    }

    // Function to save menu to a file
    void saveMenu() {
        ofstream file("menu.txt");
        for (const auto& item : menu) {
            file << item.to_string() << endl;
        }
        file.close();
        cout << "Menu saved to 'menu.txt'." << endl;
    }

    // Function to display the menu
    void displayMenu() {
        cout << "\nRestaurant Menu:" << endl;
        cout << left << setw(15) << "Item Code" << setw(25) << "Name" << setw(10) << "Price" << setw(15) << "Available" << endl;
        cout << string(70, '-') << endl;
        for (const auto& item : menu) {
            cout << left << setw(15) << item.item_code << setw(25) << item.name << setw(10) << item.price << setw(15) << item.quantity_available << endl;
        }
    }

    // Function to add a new menu item
    void addMenuItem() {
        MenuItem new_item;
        cout << "Enter Item Code: ";
        cin >> new_item.item_code;
        cout << "Enter Item Name: ";
        cin.ignore();
        getline(cin, new_item.name);
        cout << "Enter Item Price: ";
        cin >> new_item.price;
        cout << "Enter Quantity Available: ";
        cin >> new_item.quantity_available;
        menu.push_back(new_item);
        cout << "New item added to the menu." << endl;
    }

    // Function to update a menu item
    void updateMenuItem() {
        string item_code;
        cout << "Enter Item Code to update: ";
        cin >> item_code;
        for (auto& item : menu) {
            if (item.item_code == item_code) {
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, item.name);
                cout << "Enter New Price: ";
                cin >> item.price;
                cout << "Enter New Quantity Available: ";
                cin >> item.quantity_available;
                cout << "Item updated successfully." << endl;
                return;
            }
        }
        cout << "Item not found." << endl;
    }

    // Function to remove a menu item
    void removeMenuItem() {
        string item_code;
        cout << "Enter Item Code to remove: ";
        cin >> item_code;
        for (auto it = menu.begin(); it != menu.end(); ++it) {
            if (it->item_code == item_code) {
                menu.erase(it);
                cout << "Item removed successfully." << endl;
                return;
            }
        }
        cout << "Item not found." << endl;
    }

    // Function to place an order
    void placeOrder() {
        string item_code;
        int quantity;
        double total_bill = 0.0;

        while (true) {
            cout << "Enter Item Code (or type 'done' to finish): ";
            cin >> item_code;
            if (item_code == "done") {
                break;
            }
            cout << "Enter Quantity: ";
            cin >> quantity;

            for (auto& item : menu) {
                if (item.item_code == item_code) {
                    if (item.quantity_available >= quantity) {
                        item.quantity_available -= quantity;
                        total_bill += item.price * quantity;
                        order_summary[item_code] += quantity;
                        cout << "Order placed for " << quantity << " x " << item.name << endl;
                    } else {
                        cout << "Insufficient quantity available for " << item.name << endl;
                    }
                    goto next_item;
                }
            }
            cout << "Item not found." << endl;

        next_item:;
        }
        cout << "Total bill for the order: $" << total_bill << endl;
    }

    // Function to display the order summary
    void displayOrderSummary() {
        if (order_summary.empty()) {
            cout << "No orders placed yet." << endl;
            return;
        }
        cout << "\nOrder Summary:" << endl;
        cout << left << setw(15) << "Item Code" << setw(25) << "Name" << setw(10) << "Quantity" << endl;
        cout << string(50, '-') << endl;
        for (const auto& order : order_summary) {
            for (const auto& item : menu) {
                if (item.item_code == order.first) {
                    cout << left << setw(15) << order.first << setw(25) << item.name << setw(10) << order.second << endl;
                    break;
                }
            }
        }
    }
};

// User interface for the Restaurant Order Management System
void mainMenu() {
    Restaurant restaurant;
    restaurant.loadMenu();

    while (true) {
        cout << "\nRestaurant Order Management System" << endl;
        cout << "1. Display Menu" << endl;
        cout << "2. Add Menu Item" << endl;
        cout << "3. Update Menu Item" << endl;
        cout << "4. Remove Menu Item" << endl;
        cout << "5. Place Order" << endl;
        cout << "6. Display Order Summary" << endl;
        cout << "7. Save Menu" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                restaurant.displayMenu();
                break;
            case 2:
                restaurant.addMenuItem();
                break;
            case 3:
                restaurant.updateMenuItem();
                break;
            case 4:
                restaurant.removeMenuItem();
                break;
            case 5:
                restaurant.placeOrder();
                break;
            case 6:
                restaurant.displayOrderSummary();
                break;
            case 7:
                restaurant.saveMenu();
                break;
            case 8:
                cout << "Exiting the program. Goodbye!" << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// Main function
int main() {
    mainMenu();
    return 0;
}