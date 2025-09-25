
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

const int MAX_SIZE = 100;
const int FAIL_CUTOFF = 60;


void displayRecursive(const int a[], int n, int idx) {
    if (idx >= n) {
        cout << "\n";
        return;
    }
    cout << a[idx];
    if (idx < n - 1) cout << " ";
    displayRecursive(a, n, idx + 1);
}

int sumRecursive(const int a[], int n) {
    if (n == 0) return 0;
    return a[n - 1] + sumRecursive(a, n - 1);
}

int countFailingRecursive(const int a[], int n) {
    if (n == 0) return 0;
    int add = (a[n - 1] < FAIL_CUTOFF) ? 1 : 0;
    return add + countFailingRecursive(a, n - 1);
}

int maxRecursive(const int a[], int n) {
    
    if (n == 1) return a[0];
    int tailMax = maxRecursive(a, n - 1);
    return (a[n - 1] > tailMax) ? a[n - 1] : tailMax;
}


void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


int readIntInRange(const string& prompt, int lo, int hi) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= lo && x <= hi) {
            clearInput();               
            return x;
        }
        else {
            cout << "Invalid input. Enter an integer in ["
                << lo << ", " << hi << "].\n";
            clearInput();
        }
    }
}


int readIntInRangeNoPrompt(int lo, int hi) {
    int x;
    while (true) {
        if (cin >> x && x >= lo && x <= hi) {
            clearInput();
            return x;
        }
        else {
            cout << "Invalid input. Enter an integer in ["
                << lo << ", " << hi << "]: ";
            clearInput();
        }
    }
}


void waitEnter() {
    cout << "\nPress Enter to return to menu...";
    
    cin.get();
}

int main() {
    int grades[MAX_SIZE];
    int count = 0;

    cout << "****** Welcome to Recursive Grade Analyzer ******\n";

    int choice = -1;
    do {
        cout << "\nPlease choose one of the following operations:\n";
        cout << "1. Enter Grades\n";
        cout << "2. Display Grades (Recursive)\n";
        cout << "3. Calculate Average Grade (using Recursion)\n";
        cout << "4. Count Failing Grades (using Recursion)\n";
        cout << "5. Find Highest Grade (using Recursion)\n";
        cout << "6. Exit\n";

        choice = readIntInRange("Choice: ", 1, 6);

        if (choice == 1) {
            
            int n = readIntInRange("How many grades do you want to enter? ", 1, MAX_SIZE);
            for (int i = 0; i < n; ++i) {
                cout << "Enter grade #" << (i + 1) << ": ";
                int g = readIntInRangeNoPrompt(0, 100); 
                grades[i] = g;
            }
            count = n;
            cout << "Grades saved (" << count << " total).";
            waitEnter();

        }
        else if (choice == 2) {
            
            if (count == 0) {
                cout << "No grades yet. Please enter grades first.";
            }
            else {
                cout << "Grades entered:\n-> ";
                displayRecursive(grades, count, 0);
            }
            waitEnter();

        }
        else if (choice == 3) {
            
            if (count == 0) {
                cout << "No grades yet. Please enter grades first.";
            }
            else {
                int total = sumRecursive(grades, count);
                double avg = static_cast<double>(total) / static_cast<double>(count);
                cout << fixed << showpoint << setprecision(2);
                cout << "The average grade is: " << avg;
            }
            waitEnter();

        }
        else if (choice == 4) {
            
            if (count == 0) {
                cout << "No grades yet. Please enter grades first.";
            }
            else {
                int failing = countFailingRecursive(grades, count);
                cout << "Number of failing grades: " << failing;
            }
            waitEnter();

        }
        else if (choice == 5) {
            
            if (count == 0) {
                cout << "No grades yet. Please enter grades first.";
            }
            else {
                int hi = maxRecursive(grades, count);
                cout << "Highest grade: " << hi;
            }
            waitEnter();

        }
        else if (choice == 6) {
            cout << "Goodbye! Thanks for using Recursive Grade Analyzer.\n";
        }

    } while (choice != 6);

    return 0;
}
