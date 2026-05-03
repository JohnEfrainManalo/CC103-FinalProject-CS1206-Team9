#include <iostream> 
#include <string>
#include <stack>
using namespace std;

struct MyTask{
  string task;
  MyTask* next;
};

enum ActionType { ADD_ACTION, DELETE_ACTION };

struct Action {
  ActionType type;
  string task;
};

MyTask* front = nullptr;
stack<Action> undoStack;

void display_Menu();    //Completed
void addTask(string task); //Prototyped as of April 7, 2026
void delete_HP_Task(); //Prototyped as of April 7, 2026
void completeTask();
void showTasks(); //Prototyped as of April 7, 2026
void arrange_by_due_date();
void arrange_by_importance();
void undo();

//============== M A I N   F U N C T I O N ===========
int main(){
  int choice = 0;
  string task;

  do {
    display_Menu();
    cin >> choice;
    cin.ignore();

    switch (choice){
      case 1: 
        cout << "Enter the task to insert: ";
        getline(cin, task);
        addTask(task);
        break;

      case 2: 
        delete_HP_Task();
        break;

      case 3:
        break;

      case 4: 
        showTasks();
        break;

      case 5:
        break;

      case 6:
        break;

      case 7:
        undo();
        break;

      case 8: return 0;

      default:
        cout << "\nPlease enter a proper choice\n";
    };
  }
  while(choice != 8);
}
//====================================================

void display_Menu(){
  cout << "\n====== MyTask Menu ======" << endl
       << "1. Add Task" << endl
       << "2. Delete the Highhest Priority Task" << endl
       << "3. Complete Task" << endl
       << "4. Show Tasks" << endl
       << "5. Arrange Tasks by Due Date" << endl
       << "6. Arrange Tasks by Importance" << endl
       << "7. Undo" << endl
       << "8. Exit" << endl
       << "Enter choice: ";
}

void addTask(string task){
  MyTask* MyNewTask = new MyTask();
  MyNewTask->task = task;
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

  undoStack.push({ADD_ACTION, task});
}

void showTasks(){
  cout << "\n\n====== My Tasks ======" << endl;
  if (front == nullptr){
    cout << "No task listed yet." << endl;
    return;
  }
  MyTask* temp = front;
  int counter = 1;
  while (temp != nullptr){
    cout << counter << ". " << temp->task << endl;
    temp = temp->next;
    counter++;
  }
}

void delete_HP_Task(){
  if (front == nullptr){
    cout << "Tasklist is Empty. Nothing to delete." << endl;
    return;
  }
  MyTask* temp = front;
  undoStack.push({DELETE_ACTION, temp->task});
  front = temp->next;
  delete temp;
}



void undo(){
  if (undoStack.empty()){
    cout << "Nothing to undo." << endl;
    return;
  }

  Action lastAction = undoStack.top();
  undoStack.pop();

  if (lastAction.type == ADD_ACTION){
    if (front == nullptr){
      cout << "Nothing to undo." << endl;
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
    cout << "Undo: removed last added task '" << lastAction.task << "'." << endl;
  } else {
    MyTask* restored = new MyTask();
    restored->task = lastAction.task;
    restored->next = front;
    front = restored;
    cout << "Undo: restored deleted task '" << lastAction.task << "'." << endl;
  }
}

/*
By Team 9 
Members: 
  Althea Jayne I. Jayawon
  John Efrain V. Manalo
  Leneth M. Mondragon
*/