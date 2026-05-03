#include <iostream>
#include <string>
#include <stack>
#include <limits>
using namespace std;

struct MyTask{
    string task;
    int importance;
    string dueDate;
    bool complete;
    MyTask* next;
};

enum ActionType { ADD_ACTION, DELETE_ACTION, COMPLETE_ACTION };

struct Action {
    ActionType type;
    string task;
    int importance;
    string dueDate;
};

MyTask* front = nullptr;
stack<Action> undoStack;

// ================= FUNCTION PROTOTYPES =================
void display_Menu();
void addTask(string task, int importance, string dueDate);
void delete_HP_Task();
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
                    delete_HP_Task();
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

// ================= DISPLAY MENU =================
void display_Menu(){
    cout << "\n========== MY TASK MENU ==========" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Delete Highest Priority Task" << endl;
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

    try {
        MyTask* MyNewTask = new MyTask();

        MyNewTask->task = task;
        MyNewTask->importance = importance;
        MyNewTask->dueDate = dueDate;
        MyNewTask->complete = false;
        MyNewTask->next = nullptr;

        if (front == nullptr){
            front = MyNewTask;
        } else {
            MyTask* temp = front;

            while (temp->next != nullptr){
                temp = temp->next;
            }

            temp->next = MyNewTask;
        }

        undoStack.push({ADD_ACTION, task, importance, dueDate});

        cout << "\nTask added successfully.\n";

    } catch (...) {
        cout << "Failed to add task.\n";
    }
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

        cout << counter << ". ";
        cout << temp->task << endl;
        cout << "   Importance: " << temp->importance << endl;
        cout << "   Due Date : " << temp->dueDate << endl;
        cout << "   Status   : ";

        if (temp->complete){
            cout << "Completed";
        } else {
            cout << "Pending";
        }

        cout << "\n\n";

        temp = temp->next;
        counter++;
    }
}

// ================= DELETE HIGHEST PRIORITY =================
void delete_HP_Task(){

    if (front == nullptr){
        cout << "\nTask list is empty.\n";
        return;
    }

    MyTask* temp = front;
    MyTask* highest = front;

    MyTask* previous = nullptr;
    MyTask* highestPrev = nullptr;

    while (temp != nullptr){

        if (temp->importance > highest->importance){
            highest = temp;
            highestPrev = previous;
        }

        previous = temp;
        temp = temp->next;
    }

    undoStack.push({
        DELETE_ACTION,
        highest->task,
        highest->importance,
        highest->dueDate
    });

    if (highestPrev == nullptr){
        front = highest->next;
    } else {
        highestPrev->next = highest->next;
    }

    cout << "\nDeleted highest priority task: " << highest->task << endl;

    delete highest;
}

// ================= COMPLETE TASK =================
void completeTask(){

    if (front == nullptr){
        cout << "\nNo tasks available.\n";
        return;
    }

    showTasks();

    int taskNumber;

    cout << "Enter task number to complete: ";

    if (!(cin >> taskNumber)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    MyTask* temp = front;
    int counter = 1;

    while (temp != nullptr && counter < taskNumber){
        temp = temp->next;
        counter++;
    }

    if (temp == nullptr){
        cout << "Task number not found.\n";
        return;
    }

    temp->complete = true;

    undoStack.push({
        COMPLETE_ACTION,
        temp->task,
        temp->importance,
        temp->dueDate
    });

    cout << "\nTask marked as completed.\n";
}

// ================= UNDO =================
void undo(){

    if (undoStack.empty()){
        cout << "\nNothing to undo.\n";
        return;
    }

    Action lastAction = undoStack.top();
    undoStack.pop();

    // ---------- UNDO ADD ----------
    if (lastAction.type == ADD_ACTION){

        if (front == nullptr){
            cout << "Nothing to undo.\n";
            return;
        }

        MyTask* current = front;
        MyTask* previous = nullptr;

        while (current->next != nullptr){
            previous = current;
            current = current->next;
        }

        if (previous == nullptr){
            delete front;
            front = nullptr;
        } else {
            delete current;
            previous->next = nullptr;
        }

        cout << "\nUndo successful: Last added task removed.\n";
    }

    // ---------- UNDO DELETE ----------
    else if (lastAction.type == DELETE_ACTION){

        MyTask* restored = new MyTask();

        restored->task = lastAction.task;
        restored->importance = lastAction.importance;
        restored->dueDate = lastAction.dueDate;
        restored->complete = false;

        restored->next = front;
        front = restored;

        cout << "\nUndo successful: Deleted task restored.\n";
    }

    // ---------- UNDO COMPLETE ----------
    else if (lastAction.type == COMPLETE_ACTION){

        MyTask* temp = front;

        while (temp != nullptr){

            if (temp->task == lastAction.task){
                temp->complete = false;
                break;
            }

            temp = temp->next;
        }

        cout << "\nUndo successful: Completion reverted.\n";
    }
}

// ================= ARRANGE BY IMPORTANCE =================
void arrange_by_importance(){

    if (front == nullptr || front->next == nullptr){
        cout << "\nNot enough tasks to sort.\n";
        return;
    }

    bool swapped;

    do {
        swapped = false;

        MyTask* current = front;

        while (current->next != nullptr){

            if (current->importance < current->next->importance){

                swap(current->task, current->next->task);
                swap(current->importance, current->next->importance);
                swap(current->dueDate, current->next->dueDate);
                swap(current->complete, current->next->complete);

                swapped = true;
            }

            current = current->next;
        }

    } while (swapped);

    cout << "\nTasks arranged by importance.\n";
}

// ================= ARRANGE BY DUE DATE =================
void arrange_by_due_date(){

    if (front == nullptr || front->next == nullptr){
        cout << "\nNot enough tasks to sort.\n";
        return;
    }

    bool swapped;

    do {

        swapped = false;

        MyTask* current = front;

        while (current->next != nullptr){

            if (current->dueDate > current->next->dueDate){

                swap(current->task, current->next->task);
                swap(current->importance, current->next->importance);
                swap(current->dueDate, current->next->dueDate);
                swap(current->complete, current->next->complete);

                swapped = true;
            }

            current = current->next;
        }

    } while(swapped);

    cout << "\nTasks arranged by due date.\n";
}