#include <iostream> 
#include <string>
using namespace std;

struct MyTask{
  string task;
  MyTask* next;
};

MyTask* front = nullptr;

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
  return;
}
MyTask* temp = front;
while (temp->next != nullptr){
  temp = temp->next;
}
temp->next = MyNewTask;
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
  MyTask* temp = front;
  front = temp->next;
  delete temp;
}



/*
By Team 9 
Members: 
  Altha Jayne I. Jayawon
  John Efrain V. Manalo
  Leneth M. Mondragon
*/