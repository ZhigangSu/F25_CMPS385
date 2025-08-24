#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Name {
    string first;
    string last;
};

struct Scores {
    double exam1;
    double exam2;
    double exam3;
    double average;
    char letter;
};

struct Student {
    int id;
    Name name;
    string semester;
    Scores scores;
};

const int CAPACITY = 100;

void showHeader() {
    cout << "*************** Faculty Gradebook ***************\n";
    cout << "Please choose one of the following operations\n";
    cout << "1- Add a new student record\n";
    cout << "2- Enter/Update scores (by ID)\n";
    cout << "3- Display report for a student (by ID)\n";
    cout << "4- Display report for a semester\n";
    cout << "5- List all students\n";
    cout << "0- Exit\n";
    cout << "Choice: ";
}

void pauseForMenu() {
    cout << "Press any key to return to Main Menu!";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
    cout << "\n";
}

void computeAverageAndLetter(Scores& s) {
    s.average = (s.exam1 + s.exam2 + s.exam3) / 3.0;
    if (s.average >= 90.0) {
        s.letter = 'A';
    }
    else if (s.average >= 80.0) {
        s.letter = 'B';
    }
    else if (s.average >= 70.0) {
        s.letter = 'C';
    }
    else if (s.average >= 60.0) {
        s.letter = 'D';
    }
    else {
        s.letter = 'F';
    }
}

int findIndexById(Student arr[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (arr[i].id == id) return i;
    }
    return -1;
}

bool idExists(Student arr[], int count, int id) {
    return findIndexById(arr, count, id) != -1;
}

int generateUniqueId(Student arr[], int count) {
    int id = 0;
    do {
        id = 10000 + rand() % 90000;
    } while (idExists(arr, count, id));
    return id;
}

void addStudent(Student gradebook[], int& count) {
    if (count >= CAPACITY) {
        cout << "Gradebook is full. Cannot add more students.\n";
        pauseForMenu();
        return;
    }

    Student s;
    cout << "First name: ";
    cin.ignore();
    getline(cin, s.name.first);

    cout << "Last name: ";
    getline(cin, s.name.last);

    cout << "Semester (e.g., Fall 2025): ";
    getline(cin, s.semester);

    s.id = generateUniqueId(gradebook, count);

    s.scores.exam1 = 0.0;
    s.scores.exam2 = 0.0;
    s.scores.exam3 = 0.0;
    s.scores.average = 0.0;
    s.scores.letter = 'F';

    gradebook[count] = s;
    count++;

    cout << "Great! " << s.name.first << " " << s.name.last << " has been added.\n";
    cout << "Assigned Student ID: " << s.id << "\n";
    pauseForMenu();
}

double readExamScore(const string& label) {
    double x;
    cout << "Enter " << label << " (0-100): ";
    cin >> x;
    while (x < 0.0 || x > 100.0) {
        cout << "Invalid. Enter " << label << " (0-100): ";
        cin >> x;
    }
    return x;
}

void updateScores(Student gradebook[], int count) {
    if (count == 0) {
        cout << "No students added yet.\n";
        pauseForMenu();
        return;
    }

    int id;
    cout << "Enter student ID: ";
    cin >> id;

    int idx = findIndexById(gradebook, count, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        pauseForMenu();
        return;
    }

    gradebook[idx].scores.exam1 = readExamScore("Exam 1");
    gradebook[idx].scores.exam2 = readExamScore("Exam 2");
    gradebook[idx].scores.exam3 = readExamScore("Exam 3");
    computeAverageAndLetter(gradebook[idx].scores);

    cout << "Scores updated for "
        << gradebook[idx].name.first << " " << gradebook[idx].name.last
        << " (ID: " << gradebook[idx].id << ").\n";
    cout << fixed << showpoint << setprecision(2);
    cout << "Average: " << gradebook[idx].scores.average << "\n";
    cout << "Letter: " << gradebook[idx].scores.letter << "\n";
    pauseForMenu();
}

void displayStudentReport(Student gradebook[], int count) {
    if (count == 0) {
        cout << "No students added yet.\n";
        pauseForMenu();
        return;
    }

    int id;
    cout << "Enter student ID: ";
    cin >> id;

    int idx = findIndexById(gradebook, count, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        pauseForMenu();
        return;
    }

    Student& s = gradebook[idx];
    cout << "------ Student Report ------\n";
    cout << "Name: " << s.name.last << ", " << s.name.first << "\n";
    cout << "ID: " << s.id << "\n";
    cout << "Semester: " << s.semester << "\n";
    cout << "Exam 1: " << s.scores.exam1 << "\n";
    cout << "Exam 2: " << s.scores.exam2 << "\n";
    cout << "Exam 3: " << s.scores.exam3 << "\n";
    cout << fixed << showpoint << setprecision(2);
    cout << "Average: " << s.scores.average << "\n";
    cout << "Letter: " << s.scores.letter << "\n";
    cout << "----------------------------\n";
    cin.ignore();
    pauseForMenu();
}

void displaySemesterReport(Student gradebook[], int count) {
    if (count == 0) {
        cout << "No students added yet.\n";
        pauseForMenu();
        return;
    }

    cout << "Enter semester (e.g., Fall 2025): ";
    cin.ignore();
    string sem;
    getline(cin, sem);

    cout << "ID | Name | E1 E2 E3 | Avg | Letter\n";
    cout << "-------------------------------------------------------\n";

    int found = 0;
    double sumAvg = 0.0;
    double hi = -1.0;
    double lo = 101.0;

    for (int i = 0; i < count; i++) {
        if (gradebook[i].semester == sem) {
            found++;
            cout << gradebook[i].id << " | "
                << gradebook[i].name.last << ", " << gradebook[i].name.first << " | "
                << gradebook[i].scores.exam1 << " "
                << gradebook[i].scores.exam2 << " "
                << gradebook[i].scores.exam3 << " | ";
            cout << fixed << showpoint << setprecision(2)
                << gradebook[i].scores.average << " | "
                << gradebook[i].scores.letter << "\n";

            sumAvg += gradebook[i].scores.average;
            if (gradebook[i].scores.average > hi) hi = gradebook[i].scores.average;
            if (gradebook[i].scores.average < lo) lo = gradebook[i].scores.average;
        }
    }

    if (found == 0) {
        cout << "No records for that semester.\n";
        pauseForMenu();
        return;
    }

    cout << "Students: " << found << "\n";
    cout << fixed << showpoint << setprecision(2);
    cout << "Semester Average: " << (sumAvg / found) << "\n";
    cout << "Highest Average: " << hi << "\n";
    cout << "Lowest Average: " << lo << "\n";
    pauseForMenu();
}

void listAllStudents(Student gradebook[], int count) {
    if (count == 0) {
        cout << "No students added yet.\n";
        pauseForMenu();
        return;
    }

    cout << "ID | Name | Semester\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << gradebook[i].id << " | "
            << gradebook[i].name.last << ", " << gradebook[i].name.first << " | "
            << gradebook[i].semester << "\n";
    }
    pauseForMenu();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Student gradebook[CAPACITY];
    int count = 0;

    while (true) {
        showHeader();
        int choice;
        cin >> choice;

        if (choice == 0 || choice == 6) {
            cout << "Thank you for using the Faculty Gradebook!\n";
            cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
        case 1:
            addStudent(gradebook, count);
            break;
        case 2:
            updateScores(gradebook, count);
            break;
        case 3:
            displayStudentReport(gradebook, count);
            break;
        case 4:
            displaySemesterReport(gradebook, count);
            break;
        case 5:
            listAllStudents(gradebook, count);
            break;
        default:
            cout << "Invalid choice.\n";
            cin.ignore();
            pauseForMenu();
            break;
        }
    }
    return 0;
}
