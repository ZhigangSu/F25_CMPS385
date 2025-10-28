#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_APPTS = 100;
const string DATA_FILE = "appointments.txt";

template <typename T1, typename T2>
struct Appointment {
    T1 id;
    string name;
    string type;
    int timeUntil;
    T2 bill;
    string status;
};

template <typename T1, typename T2>
int loadAppointments(Appointment<T1, T2> appointments[]);

template <typename T1, typename T2>
void saveAppointments(Appointment<T1, T2> appointments[], int count);

template <typename T1, typename T2>
void addAppointment(Appointment<T1, T2> appointments[], int& count);

template <typename T1, typename T2>
void displayAppointments(Appointment<T1, T2> appointments[], int count);

template <typename T1, typename T2>
void markCompleted(Appointment<T1, T2> appointments[], int count);

template <typename T1, typename T2>
void appointmentSummary(Appointment<T1, T2> appointments[], int count);

void printTableHeader() {
    cout << "=========== APPOINTMENTS ===========" << endl;
    cout << left << setw(8) << "ID"
        << left << setw(12) << "Name"
        << left << setw(10) << "Type"
        << right << setw(6) << "Time"
        << right << setw(10) << "Bill"
        << right << setw(12) << "Status" << endl;
    cout << "-------------------------------------------------------------" << endl;
}

int main() {
    Appointment<string, float> appointments[MAX_APPTS];
    int count = loadAppointments(appointments);
    int choice;

    do {
        cout << "\n******* Welcome to Clinic Appointment Manager *******\n";
        cout << "1. Add New Appointment\n";
        cout << "2. Display All Appointments\n";
        cout << "3. Mark Appointment as Completed\n";
        cout << "4. View Appointment Summary\n";
        cout << "5. Exit\n";
        cout << "-> ";
        cin >> choice;
        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
        case 1:
            addAppointment(appointments, count);
            break;
        case 2:
            displayAppointments(appointments, count);
            break;
        case 3:
            markCompleted(appointments, count);
            break;
        case 4:
            appointmentSummary(appointments, count);
            break;
        case 5:
            saveAppointments(appointments, count);
            cout << "Data saved to appointments.txt. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

template <typename T1, typename T2>
int loadAppointments(Appointment<T1, T2> appointments[]) {
    ifstream fin(DATA_FILE);
    int count = 0;
    if (!fin.is_open()) {
        return 0;
    }

    string line;
    if (getline(fin, line)) {
        if (line.rfind("ID,Name,Type,Time,Bill,Status", 0) != 0) {
            stringstream ss(line);
            string sid, name, type, stime, sbill, status;
            if (getline(ss, sid, ',') &&
                getline(ss, name, ',') &&
                getline(ss, type, ',') &&
                getline(ss, stime, ',') &&
                getline(ss, sbill, ',') &&
                getline(ss, status)) {
                Appointment<T1, T2> a;
                a.id = sid;
                a.name = name;
                a.type = type;
                a.timeUntil = stoi(stime);
                a.bill = static_cast<T2>(stof(sbill));
                a.status = status;
                appointments[count++] = a;
            }
        }
    }

    while (count < MAX_APPTS && getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string sid, name, type, stime, sbill, status;
        if (getline(ss, sid, ',') &&
            getline(ss, name, ',') &&
            getline(ss, type, ',') &&
            getline(ss, stime, ',') &&
            getline(ss, sbill, ',') &&
            getline(ss, status)) {
            Appointment<T1, T2> a;
            a.id = sid;
            a.name = name;
            a.type = type;
            a.timeUntil = stoi(stime);
            a.bill = static_cast<T2>(stof(sbill));
            a.status = status;
            appointments[count++] = a;
        }
    }
    fin.close();
    return count;
}

template <typename T1, typename T2>
void saveAppointments(Appointment<T1, T2> appointments[], int count) {
    ofstream fout(DATA_FILE, ios::trunc);
    if (!fout.is_open()) {
        cout << "Error: cannot open file for writing.\n";
        return;
    }
    fout << "ID,Name,Type,Time,Bill,Status\n";
    for (int i = 0; i < count; i++) {
        fout << appointments[i].id << ","
            << appointments[i].name << ","
            << appointments[i].type << ","
            << appointments[i].timeUntil << ","
            << appointments[i].bill << ","
            << appointments[i].status << "\n";
    }
    fout.close();
}

template <typename T1, typename T2>
void addAppointment(Appointment<T1, T2> appointments[], int& count) {
    if (count >= MAX_APPTS) {
        cout << "Storage is full (100). Cannot add more.\n";
        return;
    }
    cin.ignore(10000, '\n');

    Appointment<T1, T2> a;
    cout << "Enter appointment ID: ";
    string idStr;
    getline(cin, idStr);
    a.id = idStr;

    cout << "Enter patient name: ";
    getline(cin, a.name);

    cout << "Enter appointment type: ";
    getline(cin, a.type);

    cout << "Enter time until appointment (hours): ";
    cin >> a.timeUntil;
    while (!cin || a.timeUntil < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid hours. Re-enter (>=0): ";
        cin >> a.timeUntil;
    }

    cout << "Enter estimated bill: ";
    T2 billTmp;
    cin >> billTmp;
    while (!cin || billTmp < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid bill. Re-enter (>=0): ";
        cin >> billTmp;
    }
    a.bill = billTmp;

    a.status = "Pending";
    appointments[count++] = a;
    cout << "Appointment added!\n";
}

template <typename T1, typename T2>
void displayAppointments(Appointment<T1, T2> appointments[], int count) {
    if (count == 0) {
        cout << "No appointments.\n";
        return;
    }
    printTableHeader();
    for (int i = 0; i < count; i++) {
        cout << left << setw(8) << appointments[i].id
            << left << setw(12) << appointments[i].name.substr(0, 11)
            << left << setw(10) << appointments[i].type.substr(0, 9)
            << right << setw(6) << appointments[i].timeUntil;

        cout << fixed << showpoint << setprecision(2);
        ostringstream os;
        os << fixed << showpoint << setprecision(2) << (double)appointments[i].bill;

        cout << right << setw(10) << ("$" + os.str())
            << right << setw(12) << appointments[i].status
            << "\n";
    }
}

template <typename T1, typename T2>
void markCompleted(Appointment<T1, T2> appointments[], int count) {
    if (count == 0) {
        cout << "No appointments.\n";
        return;
    }
    cin.ignore(10000, '\n');
    cout << "Enter appointment ID to mark as completed: ";
    string idStr;
    getline(cin, idStr);

    for (int i = 0; i < count; i++) {
        ostringstream os;
        os << appointments[i].id;
        if (os.str() == idStr) {
            appointments[i].status = "Completed";
            cout << "Appointment " << idStr << " marked as Completed.\n";
            return;
        }
    }
    cout << "Appointment ID not found.\n";
}

template <typename T1, typename T2>
void appointmentSummary(Appointment<T1, T2> appointments[], int count) {
    int completed = 0;
    int pending = 0;
    double earnings = 0.0;

    for (int i = 0; i < count; i++) {
        if (appointments[i].status == "Completed") {
            completed++;
            earnings += (double)appointments[i].bill;
        }
        else {
            pending++;
        }
    }

    cout << "======== APPOINTMENT SUMMARY ========\n";
    cout << "Total Appointments: " << count << "\n";
    cout << "Completed: " << completed << "\n";
    cout << "Pending: " << pending << "\n";
    cout << fixed << showpoint << setprecision(2);
    cout << "Total Earnings: $" << earnings << "\n";
    cout << "=====================================\n";
}


