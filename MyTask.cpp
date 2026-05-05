#include <iostream>
#include <string>
#include <stack>
#include <limits>
using namespace std;

struct MyTask{
    int id; 
    string task;
    int importance;
    string dueDate;
    bool complete;
    MyTask* next;
};

enum ActionType { ADD_ACTION, DELETE_ACTION, COMPLETE_ACTION };

struct Action {
    ActionType type;

    MyTask* node;        
    MyTask* prev;        
    MyTask dataBackup;   
};

MyTask* front = nullptr;
stack<Action> undoStack;

int taskIDCounter = 1; 

// ================= FUNCTION DECLARATIONS =================
void display_Menu();
void addTask(string task, int importance, string dueDate);
void delete_Task();
void completeTask();
void showTasks();
void arrange_by_due_date();
void arrange_by_importance();
void undo();

// ================= MAIN FUNCTION =================
int main(){
    int choice = 0;
    string task, dueDate;
    int importance;

    do {
        try {
            display_Menu();

            if (!(cin >> choice)){
                throw runtime_error("Invalid input. Please enter a number.");
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice){

                case 1:
                    cout << "Enter task name: ";
                    getline(cin, task);

                    if (task.empty()){
                        throw runtime_error("Task name cannot be empty.");
                    }

                    cout << "Enter importance level (1-10): ";
                    if (!(cin >> importance)){
                        throw runtime_error("Importance must be a number.");
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (importance < 1 || importance > 10){
                        throw runtime_error("Importance must only be between 1 and 10.");
                    }

                    cout << "Enter due date (YYYY-MM-DD): ";
                    getline(cin, dueDate);

                    addTask(task, importance, dueDate);
                    break;

                case 2:
                    delete_Task();
                    break;

                case 3:
                    completeTask();
                    break;

                case 4:
                    showTasks();
                    break;

                case 5:
                    arrange_by_due_date();
                    break;

                case 6:
                    arrange_by_importance();
                    break;

                case 7:
                    undo();
                    break;

                case 8:
                    cout << "\nExiting program...\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } catch (exception& e){
            cout << "\n[ERROR] " << e.what() << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while(choice != 8);

    return 0;
}
// ================= FUNCTION DEFINITIONS =================
// ================= DISPLAY MENU =================
void display_Menu(){
    cout << "\n========== MY TASK MENU ==========" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Delete Task" << endl;
    cout << "3. Complete Task" << endl;
    cout << "4. Show Tasks" << endl;
    cout << "5. Arrange Tasks by Due Date" << endl;
    cout << "6. Arrange Tasks by Importance" << endl;
    cout << "7. Undo" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter choice: ";
}

// ================= ADD TASK =================
void addTask(string task, int importance, string dueDate){

    MyTask* newTask = new MyTask();

    newTask->id = taskIDCounter++; 
    newTask->task = task;
    newTask->importance = importance;
    newTask->dueDate = dueDate;
    newTask->complete = false;
    newTask->next = nullptr;

    if (front == nullptr){
        front = newTask;
    } else {
        MyTask* temp = front;

        while (temp->next != nullptr){
            temp = temp->next;
        }

        temp->next = newTask;
    }

    undoStack.push({ADD_ACTION, newTask, nullptr, *newTask});

    cout << "\nTask added successfully.\n";
}

// ================= SHOW TASKS =================
void showTasks(){

    cout << "\n========== TASK LIST ==========\n";

    if (front == nullptr){
        cout << "No tasks available.\n";
        return;
    }

    MyTask* temp = front;
    int counter = 1;

    while (temp != nullptr){

        cout << counter << ". [ID: " << temp->id << "] ";
        cout << temp->task << endl;
        cout << "   Importance: " << temp->importance << endl;
        cout << "   Due Date : " << temp->dueDate << endl;
        cout << "   Status   : ";

        if (temp->complete){
            cout << "\033[32mCompleted\033[0m";
        } else {
            cout << "Pending";
        }

        cout << "\n\n";

        temp = temp->next;
        counter++;
    }
}

// ================= DELETE TASK =================
void delete_Task(){

    if (front == nullptr){
        cout << "\nNo tasks available.\n";
        return;
    }

    showTasks();

    int taskNumber;
    cout << "Enter task number to delete: ";

    if (!(cin >> taskNumber)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    MyTask* temp = front;
    MyTask* prev = nullptr;
    int counter = 1;

    while (temp != nullptr && counter < taskNumber){
        prev = temp;
        temp = temp->next;
        counter++;
    }

    if (temp == nullptr){
        cout << "Not found.\n";
        return;
    }

    undoStack.push({DELETE_ACTION, temp, prev, *temp});

    if (prev == nullptr){
        front = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;

    cout << "\nTask deleted.\n";
}

// ================= COMPLETE TASK =================
void completeTask(){

    if (front == nullptr){
        cout << "\nNo tasks.\n";
        return;
    }

    showTasks();

    int taskNumber;
    cout << "Enter task number: ";
    cin >> taskNumber;

    MyTask* temp = front;
    int counter = 1;

    while (temp != nullptr && counter < taskNumber){
        temp = temp->next;
        counter++;
    }

    if (temp == nullptr) return;

    undoStack.push({COMPLETE_ACTION, temp, nullptr, *temp});

    temp->complete = true;

    cout << "\nCompleted.\n";
}

// ================= UNDO =================
void undo(){

    if (undoStack.empty()){
        cout << "\nNothing to undo.\n";
        return;
    }

    Action last = undoStack.top();
    undoStack.pop();

    // ---------- UNDO ADD ----------
    if (last.type == ADD_ACTION){

        MyTask* temp = front;
        MyTask* prev = nullptr;

        while (temp != nullptr && temp != last.node){
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) return;

        if (prev == nullptr){
            front = temp->next;
        } else {
            prev->next = temp->next;
        }

        delete temp;

        cout << "\nUndo ADD.\n";
    }

    // ---------- UNDO DELETE ----------
    else if (last.type == DELETE_ACTION){

        MyTask* restored = new MyTask(last.dataBackup);

        if (last.prev == nullptr){
            restored->next = front;
            front = restored;
        } else {
            restored->next = last.prev->next;
            last.prev->next = restored;
        }

        cout << "\nUndo DELETE.\n";
    }

    // ---------- UNDO COMPLETE ----------
    else if (last.type == COMPLETE_ACTION){

        last.node->complete = false;

        cout << "\nUndo COMPLETE.\n";
    }
}

// ================= SORT BY IMPORTANCE =================
void arrange_by_importance(){

    if (front == nullptr || front->next == nullptr) return;

    bool swapped;

    do {
        swapped = false;

        MyTask* cur = front;

        while (cur->next != nullptr){

            if (cur->importance < cur->next->importance){

                swap(cur->id, cur->next->id);
                swap(cur->task, cur->next->task);
                swap(cur->importance, cur->next->importance);
                swap(cur->dueDate, cur->next->dueDate);
                swap(cur->complete, cur->next->complete);

                swapped = true;
            }

            cur = cur->next;
        }

    } while(swapped);

    cout << "\nSorted by importance.\n";
}

// ================= SORT BY DUE DATE =================
void arrange_by_due_date(){

    if (front == nullptr || front->next == nullptr) return;

    bool swapped;

    do {
        swapped = false;

        MyTask* cur = front;

        while (cur->next != nullptr){

            if (cur->dueDate > cur->next->dueDate){

                swap(cur->id, cur->next->id);
                swap(cur->task, cur->next->task);
                swap(cur->importance, cur->next->importance);
                swap(cur->dueDate, cur->next->dueDate);
                swap(cur->complete, cur->next->complete);

                swapped = true;
            }

            cur = cur->next;
        }

    } while(swapped);

    cout << "\nSorted by due date.\n";
}