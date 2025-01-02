#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

// Structure to store employee details
struct Employee
{
    string employeeID;
    string name;
    string designation;
    double dailyWorkingHours; // Working hours for a day
};

// Class to manage the Employee Work Tracking System
class EmployeeWorkTracker
{
private:
    vector<Employee *> employees; // Dynamic list of employees (using pointers)

public:
    // Constructor: Initializes the system by loading employee data from the file
    EmployeeWorkTracker()
    {
        loadEmployeeData();
    }

    // Destructor: Frees dynamically allocated memory
    ~EmployeeWorkTracker()
    {
        for (auto emp : employees)
        {
            delete emp;
        }
    }

    // Function to add a new employee
    void addEmployee()
    {
        Employee *newEmployee = new Employee;
        cout << "Enter Employee ID: ";
        cin >> newEmployee->employeeID;
        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin, newEmployee->name);
        cout << "Enter Employee Designation: ";
        getline(cin, newEmployee->designation);
        cout << "Enter Daily Working Hours: ";
        cin >> newEmployee->dailyWorkingHours;

        employees.push_back(newEmployee);
        cout << "Employee added successfully!" << endl;
    }

    // Function to update the working hours of an employee
    void updateWorkingHours()
    {
        string employeeID;
        cout << "Enter Employee ID to update: ";
        cin >> employeeID;

        for (auto emp : employees)
        {
            if (emp->employeeID == employeeID)
            {
                cout << "Enter updated working hours for " << emp->name << ": ";
                cin >> emp->dailyWorkingHours;
                cout << "Working hours updated successfully!" << endl;
                return;
            }
        }
        cout << "Employee not found!" << endl;
    }

    // Function to display monthly productivity report (total working hours for each employee)
    void displayProductivityReport()
    {
        cout << "\nMonthly Productivity Report (Total Working Hours)" << endl;
        cout << left << setw(20) << "Employee ID" << setw(30) << "Employee Name" << setw(20) << "Designation" << setw(20) << "Total Working Hours" << endl;
        cout << string(90, '-') << endl;

        for (auto emp : employees)
        {
            double totalWorkingHours = emp->dailyWorkingHours * 30; // Assuming 30 days of work in a month
            cout << left << setw(20) << emp->employeeID << setw(30) << emp->name << setw(20) << emp->designation << setw(20) << totalWorkingHours << endl;
        }
    }

    // Function to save employee data to a file for persistence
    void saveEmployeeData()
    {
        ofstream file("employee_data.txt");

        for (auto emp : employees)
        {
            file << emp->employeeID << ","
                 << emp->name << ","
                 << emp->designation << ","
                 << emp->dailyWorkingHours << endl;
        }

        file.close();
        cout << "Employee data saved successfully!" << endl;
    }

    // Function to load employee data from a file
    void loadEmployeeData()
    {
        ifstream file("employee_data.txt");

        if (!file)
        {
            cout << "No previous employee data found. Starting fresh." << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            Employee *emp = new Employee;
            size_t pos = 0;
            pos = line.find(',');
            emp->employeeID = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            emp->name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            emp->designation = line.substr(0, pos);
            line.erase(0, pos + 1);

            emp->dailyWorkingHours = stod(line);
            employees.push_back(emp);
        }

        file.close();
        cout << "Employee data loaded successfully!" << endl;
    }
};

// Function to display the main menu to the user
void displayMainMenu()
{
    EmployeeWorkTracker tracker;

    while (true)
    {
        cout << "\nEmployee Work Tracking System" << endl;
        cout << "1. Add New Employee" << endl;
        cout << "2. Update Employee Working Hours" << endl;
        cout << "3. View Monthly Productivity Report" << endl;
        cout << "4. Save Employee Data" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            tracker.addEmployee();
            break;
        case 2:
            tracker.updateWorkingHours();
            break;
        case 3:
            tracker.displayProductivityReport();
            break;
        case 4:
            tracker.saveEmployeeData();
            break;
        case 5:
            cout << "Exiting the system. Goodbye!" << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// Main function
int main()
{
    displayMainMenu();
    return 0;
}
