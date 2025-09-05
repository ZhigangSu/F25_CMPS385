#include <iostream>
#include <string>
using namespace std;

class Task {
private:
    int id;
    string description;
    bool done;

public:
    
    Task() {
        id = 0;
        description = "";
        done = false;
    }

   
    Task(int i, string d, bool status = false) {
        id = i;
        description = d;
        done = status;
    }

    
    int getId() {
        return id; }

    string getDescription() {
        return description; }


    bool isDone() {

        return done; }


   
    void setId(int i) {
        id = i; }


    void setDescription(string d) {
        
        description = d; }


    void setDone(bool status) {
        
        done = status; }

    
    void toggle() {
        done = !done;
    }

    
    void display() const {
        cout << "ID: " << id << " | \"" << description << "\" | Status: "
            << (done ? "Done" : "Pending") << endl;
    }
};


int findTaskById(Task tasks[], int count, int tid) {
    for (int i = 0; i < count; i++) {
        if (tasks[i].getId() == tid) {
            return i;
        }
    }
    return -1;
}

void showMenu() {
    cout << "*********** Welcome to To-Do Manager ***********" << endl;
    cout << "1 - Add task" << endl;
    cout << "2 - Toggle task (by ID)" << endl;
    cout << "3 - List pending tasks" << endl;
    cout << "0 - Exit" << endl;
    cout << "Choice: ";
}

int main() {
    Task tasks[50];
    int count = 0;
    int nextId = 1001;

    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) {
            string desc;
            cout << "Enter description: ";
            getline(cin, desc);

            tasks[count] = Task(nextId, desc, false);
            cout << "Task added! ID: " << nextId << endl;

            nextId++;
            count++;

        }
        else if (choice == 2) {
            int tid;
            cout << "Enter Task ID: ";
            cin >> tid;

            int idx = findTaskById(tasks, count, tid);
            if (idx != -1) {
                tasks[idx].toggle();
                cout << "Toggled task " << tid << "." << endl;
            }
            else {
                cout << "Task not found." << endl;
            }

        }
        else if (choice == 3) {
            bool any = false;
            for (int i = 0; i < count; i++) {
                if (!tasks[i].isDone()) {
                    tasks[i].display();
                    any = true;
                }
            }
            if (!any) {
                cout << "No pending tasks." << endl;
            }

        }
        else if (choice == 0) {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
