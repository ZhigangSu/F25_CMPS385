#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Date {
    int month;
    int day;
    int year;
};

struct Appointment {
    int id;
    string name;
    Date date;
    string purpose;
};

Appointment schedule[50];
int countAppointments = 0;

int generateId() {
    return 1000 + rand() % 9000;
}

void showHeader() {
    cout << "*********** Appointment Scheduler ***********\n";
    cout << "1. Add Appointment\n";
    cout << "2. View Appointments by Date\n";
    cout << "3. Exit\n";
}

void addAppointment() {
    if (countAppointments >= 50) {
        cout << "Schedule is full. Cannot add more appointments.\n";
        return;
    }
    Appointment a;
    cout << "Name: ";
    cin.ignore();
    getline(cin, a.name);
    cout << "Date (MM DD YYYY): ";
    cin >> a.date.month >> a.date.day >> a.date.year;
    cout << "Purpose: ";
    cin.ignore();
    getline(cin, a.purpose);
    a.id = generateId();
    schedule[countAppointments] = a;
    countAppointments++;
    cout << "\nAppointment added! ID: " << a.id << "\n\n";
}

void viewByDate() {
    int m, d, y;
    cout << "Enter date (MM DD YYYY): ";
    cin >> m >> d >> y;
    bool any = false;
    cout << "\nAppointments on "
        << setw(2) << setfill('0') << m << "/"
        << setw(2) << setfill('0') << d << "/"
        << y << ":\n";
    for (int i = 0; i < countAppointments; ++i) {
        const Appointment& a = schedule[i];
        if (a.date.month == m && a.date.day == d && a.date.year == y) {
            cout << "ID: " << a.id << " | " << a.name << " | " << a.purpose << "\n";
            any = true;
        }
    }
    if (!any) {
        cout << "No appointments for this date.\n";
    }
    cout << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    while (true) {
        showHeader();
        cout << "\nChoice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input.\n\n";
            continue;
        }
        if (choice == 1) {
            addAppointment();
            cout << "---------------------------------------------\n\n";
        }
        else if (choice == 2) {
            viewByDate();
            cout << "---------------------------------------------\n\n";
        }
        else if (choice == 3) {
            cout << "Thank you for using the scheduler!\n";
            break;
        }
        else {
            cout << "Please choose 1, 2, or 3.\n\n";
        }
    }
    return 0;
}
