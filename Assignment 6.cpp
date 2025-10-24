#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <type_traits>
using namespace std;

template <typename T1, typename T2>
struct Package {
    T1 id;
    string name;
    string type;
    int etaHours;
    T2 fee;
    string status;
};

template <typename T>
T parseValue(const string& s) {
    if constexpr (is_same<T, int>::value) {
        return static_cast<T>(stoi(s));
    }
    else if constexpr (is_same<T, long>::value) {
        return static_cast<T>(stol(s));
    }
    else if constexpr (is_same<T, double>::value) {
        return static_cast<T>(stod(s));
    }
    else if constexpr (is_same<T, float>::value) {
        return static_cast<T>(stof(s));
    }
    else {
        return static_cast<T>(s);
    }
}

static void splitCSV(const string& line, string parts[], int expected) {
    string token;
    stringstream ss(line);
    int i = 0;
    while (getline(ss, token, ',') && i < expected) {
        parts[i++] = token;
    }
    while (i < expected) {
        parts[i++] = "";
    }
}

template <typename T1, typename T2>
int loadPackages(Package<T1, T2> packages[]);

template <typename T1, typename T2>
void savePackages(Package<T1, T2> packages[], int count);

template <typename T1, typename T2>
void addPackage(Package<T1, T2> packages[], int& count);

template <typename T1, typename T2>
void displayPackages(Package<T1, T2> packages[], int count);

template <typename T1, typename T2>
void markDelivered(Package<T1, T2> packages[], int count);

template <typename T1, typename T2>
void deliveryReport(Package<T1, T2> packages[], int count);

template <typename T1, typename T2>
int loadPackages(Package<T1, T2> packages[]) {
    ifstream fin("packages.txt");
    if (!fin) {
        return 0;
    }
    string line;
    int count = 0;

    streampos pos = fin.tellg();
    if (getline(fin, line)) {
        if (line.rfind("ID,", 0) != 0) {
            fin.clear();
            fin.seekg(pos);
        }
    }
    else {
        return 0;
    }

    while (getline(fin, line)) {
        if (line.size() == 0) continue;
        string parts[6];
        splitCSV(line, parts, 6);

        if (count >= 100) {
            cout << "Warning: Maximum capacity (100) reached while loading.\n";
            break;
        }

        Package<T1, T2> p;
        p.id = parseValue<T1>(parts[0]);
        p.name = parts[1];
        p.type = parts[2];
        p.etaHours = (parts[3].empty() ? 0 : stoi(parts[3]));
        p.fee = parseValue<T2>(parts[4]);
        p.status = parts[5].empty() ? "Pending" : parts[5];

        packages[count++] = p;
    }
    fin.close();
    return count;
}

template <typename T1, typename T2>
void savePackages(Package<T1, T2> packages[], int count) {
    ofstream fout("packages.txt");
    if (!fout) {
        cout << "Error: Unable to write to packages.txt\n";
        return;
    }
    fout << "ID,Name,Type,ETA,Fee,Status\n";
    for (int i = 0; i < count; ++i) {
        fout << packages[i].id << ","
            << packages[i].name << ","
            << packages[i].type << ","
            << packages[i].etaHours << ","
            << packages[i].fee << ","
            << packages[i].status << "\n";
    }
    fout.close();
}

template <typename T1, typename T2>
void addPackage(Package<T1, T2> packages[], int& count) {
    if (count >= 100) {
        cout << "Storage full. Cannot add more packages.\n";
        return;
    }

    Package<T1, T2> p;
    cout << "Enter package ID: ";
    if constexpr (is_same<T1, int>::value) {
        cin >> p.id;
    }
    else {
        cin >> p.id;
    }
    cin.ignore(10000, '\n');

    cout << "Enter recipient name: ";
    getline(cin, p.name);

    cout << "Enter delivery type (Standard/Express/Fragile): ";
    getline(cin, p.type);

    cout << "Enter delivery ETA (in hours): ";
    cin >> p.etaHours;

    cout << "Enter delivery fee: ";
    if constexpr (is_same<T2, double>::value || is_same<T2, float>::value) {
        cin >> p.fee;
    }
    else {
        cin >> p.fee;
    }

    p.status = "Pending";

    packages[count] = p;
    count = count + 1;

    cout << "Package added!\n";
}

template <typename T1, typename T2>
void displayPackages(Package<T1, T2> packages[], int /*count*/) {
    ifstream fin("packages.txt");
    if (!fin) {
        cout << "No packages.txt found. Nothing to display.\n";
        return;
    }

    string line;
    if (getline(fin, line)) {
        if (line.rfind("ID,", 0) != 0) {
            fin.clear();
            fin.seekg(0);
        }
    }
    cout << "============ PACKAGES ============\n";
    cout << left << setw(8) << "ID"
        << left << setw(12) << "Name"
        << left << setw(10) << "Type"
        << right << setw(6) << "ETA"
        << right << setw(10) << "Fee"
        << right << setw(12) << "Status" << "\n";
    cout << "-----------------------------------------------\n";

    cout << fixed << showpoint << setprecision(2);

    while (getline(fin, line)) {
        if (line.size() == 0) continue;
        string parts[6];
        splitCSV(line, parts, 6);

        string feeStr = parts[4];
        double feeVal = 0.0;
        if (!feeStr.empty()) {
            try { feeVal = stod(feeStr); }
            catch (...) { feeVal = 0.0; }
        }

        cout << left << setw(8) << parts[0]
            << left << setw(12) << parts[1]
            << left << setw(10) << parts[2]
            << right << setw(6) << parts[3]
            << right << setw(3) << "$" << setw(7) << feeVal
            << right << setw(12) << (parts[5].empty() ? "Pending" : parts[5])
            << "\n";
    }
    fin.close();
}

template <typename T1, typename T2>
void markDelivered(Package<T1, T2> packages[], int count) {
    cout << "Enter package ID to mark as delivered: ";
    T1 target;
    if constexpr (is_same<T1, int>::value) {
        cin >> target;
    }
    else {
        cin >> target;
    }

    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (packages[i].id == target) {
            packages[i].status = "Delivered";
            cout << "Package " << packages[i].id << " marked as Delivered.\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Package not found in memory.\n";
    }
}

template <typename T1, typename T2>
void deliveryReport(Package<T1, T2> packages[], int count) {
    int total = count;
    int delivered = 0;
    double revenue = 0.0;

    for (int i = 0; i < count; ++i) {
        if (packages[i].status == "Delivered") {
            delivered = delivered + 1;
            revenue = revenue + static_cast<double>(packages[i].fee);
        }
    }

    cout << "========== DELIVERY REPORT ==========\n";
    cout << "Total Packages: " << total << "\n";
    cout << "Delivered: " << delivered << "\n";
    cout << "Pending: " << (total - delivered) << "\n";
    cout << fixed << showpoint << setprecision(2);
    cout << "Total Revenue: $" << revenue << "\n";
    cout << "=====================================\n";
}

int main() {
    Package<int, double> packages[100];
    int count = loadPackages(packages);
    int choice;

    do {
        cout << "\n******** Welcome to Package Delivery Tracker ********\n";
        cout << "1. Add New Package\n";
        cout << "2. Display All Packages\n";
        cout << "3. Mark Package as Delivered\n";
        cout << "4. View Delivery Report\n";
        cout << "5. Exit\n";
        cout << "-> ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPackage(packages, count);
            break;
        case 2:
            displayPackages(packages, count);
            break;
        case 3:
            markDelivered(packages, count);
            break;
        case 4:
            deliveryReport(packages, count);
            break;
        case 5:
            savePackages(packages, count);
            cout << "Data saved to packages.txt. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
