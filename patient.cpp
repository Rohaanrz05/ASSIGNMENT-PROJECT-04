#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> // For sorting

using namespace std;

// Structure to store patient details
struct Patient
{
    string patient_id;
    string name;
    int age;
    string disease;
    string room_number;

    // Function to convert patient details to a string for saving to file
    string to_string() const
    {
        return patient_id + "," + name + "," + std::to_string(age) + "," + disease + "," + room_number;
    }
};

// Class to manage the hospital patient records
class Hospital
{
private:
    vector<Patient> patients;

public:
    // Function to add a new patient
    void addPatient(const Patient &patient)
    {
        patients.push_back(patient);
        cout << "Patient '" << patient.name << "' added to records." << endl;
    }

    // Function to discharge a patient by ID
    void dischargePatient(const string &patient_id)
    {
        auto it = remove_if(patients.begin(), patients.end(),
                            [&patient_id](const Patient &patient)
                            { return patient.patient_id == patient_id; });
        if (it != patients.end())
        {
            patients.erase(it, patients.end());
            cout << "Patient with ID '" << patient_id << "' has been discharged." << endl;
        }
        else
        {
            cout << "Patient with ID '" << patient_id << "' not found." << endl;
        }
    }

    // Function to search for a patient by ID
    Patient *searchPatient(const string &patient_id)
    {
        for (auto &patient : patients)
        {
            if (patient.patient_id == patient_id)
            {
                return &patient;
            }
        }
        return nullptr;
    }

    // Function to display all admitted patients
    void displayPatients()
    {
        if (patients.empty())
        {
            cout << "No patients currently admitted." << endl;
            return;
        }
        cout << "\nAdmitted Patients:" << endl;
        for (const auto &patient : patients)
        {
            cout << "ID: " << patient.patient_id << ", Name: " << patient.name
                 << ", Age: " << patient.age << ", Disease: " << patient.disease
                 << ", Room Number: " << patient.room_number << endl;
        }
    }

    // Function to sort patients by name
    void displaySortedPatients()
    {
        if (patients.empty())
        {
            cout << "No patients currently admitted to sort." << endl;
            return;
        }
        vector<Patient> sorted_patients = patients;
        sort(sorted_patients.begin(), sorted_patients.end(),
             [](const Patient &a, const Patient &b)
             { return a.name < b.name; });

        cout << "\nPatients Sorted by Name:" << endl;
        for (const auto &patient : sorted_patients)
        {
            cout << "ID: " << patient.patient_id << ", Name: " << patient.name
                 << ", Age: " << patient.age << ", Disease: " << patient.disease
                 << ", Room Number: " << patient.room_number << endl;
        }
    }

    // Function to update a patient's disease or room number
    void updatePatient(const string &patient_id, const string &new_disease, const string &new_room_number)
    {
        for (auto &patient : patients)
        {
            if (patient.patient_id == patient_id)
            {
                patient.disease = new_disease;
                patient.room_number = new_room_number;
                cout << "Patient details updated for '" << patient.name << "'." << endl;
                return;
            }
        }
        cout << "Patient with ID '" << patient_id << "' not found." << endl;
    }

    // Function to save patient records to a file
    void saveRecords()
    {
        ofstream file("patients.txt");
        for (const auto &patient : patients)
        {
            file << patient.to_string() << endl;
        }
        file.close();
        cout << "Patient records saved to 'patients.txt'." << endl;
    }

    // Function to load patient records from a file
    void loadRecords()
    {
        ifstream file("patients.txt");
        if (!file)
        {
            cout << "No previous records found. Starting with an empty hospital." << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            Patient patient;
            string age_str;
            getline(ss, patient.patient_id, ',');
            getline(ss, patient.name, ',');
            getline(ss, age_str, ',');
            patient.age = stoi(age_str);
            getline(ss, patient.disease, ',');
            getline(ss, patient.room_number, ',');
            patients.push_back(patient);
        }
        file.close();
        cout << "Patient records loaded from 'patients.txt'." << endl;
    }
};

// User interface for the Hospital Patient Management System
void mainMenu()
{
    Hospital hospital;
    hospital.loadRecords();

    while (true)
    {
        cout << "\nHospital Patient Management System" << endl;
        cout << "1. Add a new patient" << endl;
        cout << "2. Discharge a patient" << endl;
        cout << "3. Search for a patient by ID" << endl;
        cout << "4. Display all admitted patients" << endl;
        cout << "5. Display patients sorted by name" << endl;
        cout << "6. Update a patient's details" << endl;
        cout << "7. Save patient records" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        if (choice == 1)
        {
            Patient new_patient;
            cout << "Enter Patient ID: ";
            getline(cin, new_patient.patient_id);
            cout << "Enter Patient Name: ";
            getline(cin, new_patient.name);
            cout << "Enter Patient Age: ";
            cin >> new_patient.age;
            cin.ignore(); // Clear the newline character from the input buffer
            cout << "Enter Disease: ";
            getline(cin, new_patient.disease);
            cout << "Enter Room Number: ";
            getline(cin, new_patient.room_number);
            hospital.addPatient(new_patient);
        }
        else if (choice == 2)
        {
            string patient_id;
            cout << "Enter Patient ID to discharge: ";
            getline(cin, patient_id);
            hospital.dischargePatient(patient_id);
        }
        else if (choice == 3)
        {
            string patient_id;
            cout << "Enter Patient ID to search: ";
            getline(cin, patient_id);
            Patient *patient = hospital.searchPatient(patient_id);
            if (patient)
            {
                cout << "\nPatient Details:" << endl;
                cout << "ID: " << patient->patient_id << ", Name: " << patient->name
                     << ", Age: " << patient->age << ", Disease: " << patient->disease
                     << ", Room Number: " << patient->room_number << endl;
            }
            else
            {
                cout << "Patient not found." << endl;
            }
        }
        else if (choice == 4)
        {
            hospital.displayPatients();
        }
        else if (choice == 5)
        {
            hospital.displaySortedPatients();
        }
        else if (choice == 6)
        {
            string patient_id, new_disease, new_room_number;
            cout << "Enter Patient ID to update: ";
            getline(cin, patient_id);
            cout << "Enter new disease: ";
            getline(cin, new_disease);
            cout << "Enter new room number: ";
            getline(cin, new_room_number);
            hospital.updatePatient(patient_id, new_disease, new_room_number);
        }
        else if (choice == 7)
        {
            hospital.saveRecords();
        }
        else if (choice == 8)
        {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// Main function
int main()
{
    mainMenu();
    return 0;
}