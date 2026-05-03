#include <iostream>
#include <string>
using namespace std;

struct MyTask{
    string task;
    int importance;
    string dueDate;
    bool complete;
    MyTask* next;
};

MyTask* front = nullptr;

void display_Menu();    //Completed
void addTask(string task); //Prototyped as of April 7, 2026
void delete_HP_Task(); //Prototyped as of April 7, 2026
void completeTask();
void showTasks();
void arrange_by_due_date();
void arrange_by_importance();
void undo();

// ================= MAIN FUNCTION =================
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
    cout << "Tasklist is Empty. Nothing to delete." << endl;
    return;
  }
  MyTask* temp = front;
  front = temp->next;
  delete temp;
}



/*
By Team 9 
Members: 
  Althea Jayne I. Jayawon
  John Efrain V. Manalo
  Leneth M. Mondragon
*/