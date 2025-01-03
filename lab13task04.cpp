#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
struct Employee
{
    int id;
    string name;
    string designation;
    int totalHours;

    Employee(int empId, const string &empName, const string &empDesignation, int hours = 0)
        : id(empId), name(empName), designation(empDesignation), totalHours(hours) {}
};

void addEmployee(vector<Employee> &employees);
void updateWorkingHours(vector<Employee> &employees);
void generateMonthlyReport(const vector<Employee> &employees);
void saveToFile(const vector<Employee> &employees, const string &filename);
void loadFromFile(vector<Employee> &employees, const string &filename);

int main()
{
    vector<Employee> employees;
    string filename = "employees_data.txt";

    loadFromFile(employees, filename);

    int choice;
    do
    {
        cout << "\n===== Employee Work Tracking System =====\n";
        cout << "1. Add New Employee\n";
        cout << "2. Update Employee Working Hours\n";
        cout << "3. View Monthly Productivity Report\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addEmployee(employees);
            break;
        case 2:
            updateWorkingHours(employees);
            break;
        case 3:
            generateMonthlyReport(employees);
            break;
        case 4:
            saveToFile(employees, filename);
            cout << "Data saved successfully. Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void addEmployee(vector<Employee> &employees)
{
    int id;
    string name, designation;

    cout << "Enter Employee ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Employee Name: ";
    getline(cin, name);
    cout << "Enter Employee Designation: ";
    getline(cin, designation);

    employees.emplace_back(id, name, designation);
    cout << "Employee added successfully!\n";
}

void updateWorkingHours(vector<Employee> &employees)
{
    int id, hours;
    cout << "Enter Employee ID: ";
    cin >> id;

    for (auto &emp : employees)
    {
        if (emp.id == id)
        {
            cout << "Enter hours to add for " << emp.name << ": ";
            cin >> hours;
            emp.totalHours += hours;
            cout << "Working hours updated successfully!\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

void generateMonthlyReport(const vector<Employee> &employees)
{
    cout << "\n===== Monthly Productivity Report =====\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "Designation" << setw(15) << "Total Hours\n";
    cout << string(65, '-') << "\n";

    for (const auto &emp : employees)
    {
        cout << left << setw(10) << emp.id << setw(20) << emp.name << setw(20) << emp.designation << setw(15) << emp.totalHours << "\n";
    }
}

void saveToFile(const vector<Employee> &employees, const string &filename)
{
    ofstream outFile(filename, ios::trunc);

    if (!outFile)
    {
        cerr << "Error saving data to file.\n";
        return;
    }

    for (const auto &emp : employees)
    {
        outFile << emp.id << '\n'
                << emp.name << '\n'
                << emp.designation << '\n'
                << emp.totalHours << '\n';
    }
    outFile.close();
}

void loadFromFile(vector<Employee> &employees, const string &filename)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }

    int id, totalHours;
    string name, designation;

    while (inFile >> id)
    {
        rtyyytttttt

        inFile.ignore();
        getline(inFile, name);
        getline(inFile, designation);
        inFile >> totalHours;
        inFile.ignore();

        employees.emplace_back(id, name, designation, totalHours);
    }
    inFile.close();
}