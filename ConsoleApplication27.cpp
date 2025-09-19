#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


class Item {
private:
    string name;
    double price;

protected:
    
    Item(const string& n, double p) {
        name = n;
        price = p;
    }
    
    const string& nameValue() const { return name; }
    double priceValue() const { return price; }

public:
    virtual ~Item() {}

    
    virtual void display() const = 0;       
    virtual double getPrice() const = 0;    
    virtual void receiptEntry() const = 0;  

    
    string getName() const { return name; }
};


class FoodItem : public Item {
private:
    string expirationDate;

public:
    
    FoodItem(const string& n, double p, const string& exp)
        : Item(n, p) {
        expirationDate = exp;
    }

    void display() const override {
        cout << "Name: " << nameValue()
            << " | Price: $" << fixed << setprecision(2) << priceValue()
            << " | Exp: " << expirationDate << "\n";
    }

    double getPrice() const override {
        return priceValue();
    }

    void receiptEntry() const override {
        cout << nameValue() << " - $" << fixed << setprecision(2) << priceValue() << "\n";
    }
};


class ElectronicItem : public Item {
private:
    int warrantyMonths;

public:
    ElectronicItem(const string& n, double p, int w)
        : Item(n, p) {
        warrantyMonths = w;
    }

    void display() const override {
        cout << "Name: " << nameValue()
            << " | Price: $" << fixed << setprecision(2) << priceValue()
            << " | Warranty: " << warrantyMonths << " months\n";
    }

    double getPrice() const override {
        return priceValue();
    }

    void receiptEntry() const override {
        cout << nameValue() << " - $" << fixed << setprecision(2) << priceValue() << "\n";
    }
};

int main() {
    
    Item* store[50];
    int storeCount = 0;

    Item* purchases[20];
    int purchaseCount = 0;

    cout << "************* Welcome to QuickMart POS *************\n";

    int choice = -1;
    do {
        cout << "1 - Add item to store\n";
        cout << "2 - Display available items\n";
        cout << "3 - Buy item by name\n";
        cout << "4 - View receipt\n";
        cout << "0 - Exit\n";
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore(10000, '\n'); 

        if (choice == 1) {
            if (storeCount >= 50) {
                cout << "Store is full.\n";
                continue;
            }

            string type;
            cout << "Enter item type (Food/Electronic): ";
            getline(cin, type);

            string name;
            double price;
            cout << "Enter item name: ";
            getline(cin, name);
            cout << "Enter price: ";
            if (!(cin >> price)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid price.\n";
                continue;
            }
            cin.ignore(10000, '\n');

            if (type == "Food" || type == "food" || type == "FOOD") {
                string exp;
                cout << "Enter expiration date: ";
                getline(cin, exp);
                store[storeCount++] = new FoodItem(name, price, exp);
                cout << "Item added successfully!\n";
            }
            else if (type == "Electronic" || type == "electronic" || type == "ELECTRONIC") {
                int w;
                cout << "Enter warranty in months: ";
                if (!(cin >> w)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid warranty.\n";
                    continue;
                }
                cin.ignore(10000, '\n');
                store[storeCount++] = new ElectronicItem(name, price, w);
                cout << "Item added successfully!\n";
            }
            else {
                cout << "Unknown type.\n";
            }
        }
        else if (choice == 2) {
            if (storeCount == 0) {
                cout << "No items in store.\n";
            }
            else {
                for (int i = 0; i < storeCount; ++i) {
                    store[i]->display();
                }
            }
        }
        else if (choice == 3) {
            if (storeCount == 0) {
                cout << "No items in store.\n";
                continue;
            }
            if (purchaseCount >= 20) {
                cout << "Purchase list is full.\n";
                continue;
            }

            string qname;
            cout << "Enter name of item to purchase: ";
            getline(cin, qname);

            int found = -1;
            for (int i = 0; i < storeCount; ++i) {
                if (store[i]->getName() == qname) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                cout << "Item not found.\n";
            }
            else {
                purchases[purchaseCount++] = store[found];
                cout << "Purchased " << store[found]->getName()
                    << " for $" << fixed << setprecision(2) << store[found]->getPrice() << "\n";
            }
        }
        else if (choice == 4) {
            cout << "---- Receipt ----\n";
            if (purchaseCount == 0) {
                cout << "(empty)\n";
            }
            else {
                double total = 0.0;
                for (int i = 0; i < purchaseCount; ++i) {
                    cout << (i + 1) << ". ";
                    purchases[i]->receiptEntry();
                    total += purchases[i]->getPrice();
                }
                cout << "Total: $" << fixed << setprecision(2) << total << "\n";
            }
        }
        else if (choice == 0) {
            cout << "Thank you for shopping at QuickMart!\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    
    for (int i = 0; i < storeCount; ++i) {
        delete store[i];
        store[i] = nullptr; 
    }

    return 0;
}
