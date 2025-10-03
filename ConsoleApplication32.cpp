#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_ITEMS = 100;

struct Item {
    string name;
    string category;
    int quantity;
    double price;
};

struct Transaction {
    string type;
    string itemName;
    int quantity;
    double unitPrice;
};

string trim(const string& s) {
    int start = 0;
    int end = s.size() - 1;
    while (start <= end && (s[start] == ' ' || s[start] == '\t' || s[start] == '\n' || s[start] == '\r')) start++;
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n' || s[end] == '\r')) end--;
    if (start > end) return "";
    return s.substr(start, end - start + 1);
}

int loadInventory(Item items[]) {
    ifstream fin("inventory.txt");
    if (!fin) return 0;
    string line;
    getline(fin, line);
    int count = 0;
    while (getline(fin, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);
        string name, cat, qtyStr, priceStr;
        getline(ss, name, ',');
        getline(ss, cat, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr, ',');
        items[count].name = trim(name);
        items[count].category = trim(cat);
        items[count].quantity = stoi(trim(qtyStr));
        items[count].price = stod(trim(priceStr));
        count++;
    }
    return count;
}

void saveInventory(Item items[], int count) {
    ofstream fout("inventory.txt");
    fout << "Name,Category,Quantity,Price\n";
    for (int i = 0; i < count; i++) {
        fout << items[i].name << ","
            << items[i].category << ","
            << items[i].quantity << ","
            << items[i].price << "\n";
    }
}

void saveTransaction(const Transaction& t) {
    ifstream test("transactions.txt");
    bool needHeader = !test.good();
    ofstream fout("transactions.txt", ios::app);
    if (needHeader) fout << "Type,ItemName,Quantity,UnitPrice\n";
    fout << t.type << "," << t.itemName << "," << t.quantity << "," << t.unitPrice << "\n";
}

void displayInventory(Item items[], int count) {
    cout << "============== INVENTORY ==============\n";
    cout << left << setw(15) << "Item Name"
        << left << setw(15) << "Category"
        << right << setw(8) << "Qty"
        << right << setw(10) << "Price" << endl;
    cout << "---------------------------------------------\n";
    cout << fixed << showpoint << setprecision(2);
    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << items[i].name
            << left << setw(15) << items[i].category
            << right << setw(8) << items[i].quantity
            << right << setw(6) << "$" << items[i].price << endl;
    }
}

int findItem(Item items[], int count, string name) {
    for (int i = 0; i < count; i++) {
        if (items[i].name == name) return i;
    }
    return -1;
}

void addItem(Item items[], int& count) {
    if (count >= MAX_ITEMS) {
        cout << "Inventory full!" << endl;
        return;
    }
    cout << "Enter item name: ";
    getline(cin, items[count].name);
    cout << "Enter category: ";
    getline(cin, items[count].category);
    cout << "Enter quantity: ";
    cin >> items[count].quantity;
    cout << "Enter price: ";
    cin >> items[count].price;
    cin.ignore(1000, '\n');
    cout << "Item added!" << endl;
    count++;
}

void buyItem(Item items[], int count) {
    string name; int qty;
    cout << "Enter item to buy: ";
    getline(cin, name);
    cout << "Quantity: ";
    cin >> qty;
    cin.ignore(1000, '\n');
    int idx = findItem(items, count, name);
    if (idx == -1) { cout << "Item not found!" << endl; return; }
    if (items[idx].quantity < qty) { cout << "Not enough stock!" << endl; return; }
    items[idx].quantity -= qty;
    double total = qty * items[idx].price;
    Transaction t = { "BUY", items[idx].name, qty, items[idx].price };
    saveTransaction(t);
    cout << fixed << showpoint << setprecision(2);
    cout << "Successfully purchased " << qty << " x " << name << " for $" << total << endl;
}

void returnItem(Item items[], int count) {
    string name; int qty;
    cout << "Enter item to return: ";
    getline(cin, name);
    cout << "Quantity: ";
    cin >> qty;
    cin.ignore(1000, '\n');
    int idx = findItem(items, count, name);
    if (idx == -1) { cout << "Item not found!" << endl; return; }
    items[idx].quantity += qty;
    Transaction t = { "RETURN", items[idx].name, qty, items[idx].price };
    saveTransaction(t);
    cout << qty << " x " << name << " returned and added back to inventory." << endl;
}

void showProfit() {
    ifstream fin("transactions.txt");
    if (!fin) { cout << "No transactions yet." << endl; return; }
    string line;
    getline(fin, line);
    double revenue = 0, refund = 0;
    while (getline(fin, line)) {
        stringstream ss(line);
        string type, name, qtyStr, priceStr;
        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr, ',');
        int qty = stoi(trim(qtyStr));
        double price = stod(trim(priceStr));
        if (type == "BUY") revenue += qty * price;
        else if (type == "RETURN") refund += qty * price;
    }
    cout << "========== PROFIT REPORT ==========\n";
    cout << fixed << showpoint << setprecision(2);
    cout << "Total Revenue: $" << revenue << endl;
    cout << "Total Refunds: $" << refund << endl;
    cout << "Net Profit:    $" << revenue - refund << endl;
    cout << "==================================\n";
}

void showMenu() {
    cout << "******** Welcome to Store Inventory & Profit Tracker ********\n";
    cout << "Please choose one of the following operations:\n";
    cout << "1. Add New Item to Inventory\n";
    cout << "2. Display Inventory\n";
    cout << "3. Buy Item\n";
    cout << "4. Return Item\n";
    cout << "5. View Profit Report\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";   
}

int main() {
    Item items[MAX_ITEMS];
    int count = loadInventory(items);
    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(1000, '\n');
        if (choice == 1) addItem(items, count);
        else if (choice == 2) displayInventory(items, count);
        else if (choice == 3) buyItem(items, count);
        else if (choice == 4) returnItem(items, count);
        else if (choice == 5) showProfit();
        else if (choice == 6) {
            saveInventory(items, count);
            cout << "Inventory and transactions saved. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
