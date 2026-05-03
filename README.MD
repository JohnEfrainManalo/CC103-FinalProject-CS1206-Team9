# MyTask Manager System (C++)

## Overview

The **MyTask Manager System** is a console-based task management application written in C++. It uses:

* Linked Lists
* Stack Data Structure
* Sorting Algorithms
* Exception Handling
* Dynamic Memory Allocation

The program allows users to:

* Add tasks
* Delete the highest priority task
* Complete tasks
* View tasks
* Arrange tasks by importance
* Arrange tasks by due date
* Undo actions

This project demonstrates the practical implementation of fundamental Data Structures and Algorithms concepts.

---

# Features

## 1. Add Task

Users can add a new task with:

* Task name
* Importance level
* Due date

Example:

```text
Task Name: Finish Assignment
Importance: 9
Due Date: 2026-05-10
```

---

## 2. Delete Highest Priority Task

The program automatically finds and removes the task with the highest importance value.

Example:

```text
Deleted highest priority task: Finish Assignment
```

---

## 3. Complete Task

Users can mark tasks as completed.

Completed tasks will display:

```text
Status: Completed
```

---

## 4. Show Tasks

Displays all tasks currently stored in the linked list.

Each task displays:

* Task name
* Importance level
* Due date
* Completion status

---

## 5. Arrange Tasks by Due Date

Tasks are sorted from earliest due date to latest due date.

The sorting algorithm used is:

* Bubble Sort

---

## 6. Arrange Tasks by Importance

Tasks are sorted from highest importance to lowest importance.

The sorting algorithm used is:

* Bubble Sort

---

## 7. Undo Feature

The system stores actions inside a Stack.

Supported undo actions:

* Undo Add
* Undo Delete
* Undo Complete

This follows the:

* LIFO (Last In First Out) principle

---

# Data Structures Used

| Data Structure | Purpose                 |
| -------------- | ----------------------- |
| Linked List    | Store tasks dynamically |
| Stack          | Undo functionality      |

---

# Program Structure

## Task Node Structure

```cpp
struct MyTask{
    string task;
    int importance;
    string dueDate;
    bool complete;
    MyTask* next;
};
```

### Explanation

| Variable   | Purpose                  |
| ---------- | ------------------------ |
| task       | Stores task name         |
| importance | Stores priority level    |
| dueDate    | Stores task deadline     |
| complete   | Tracks completion status |
| next       | Pointer to next node     |

---

# Undo Action Structure

```cpp
struct Action {
    ActionType type;
    string task;
    int importance;
    string dueDate;
};
```

This structure stores action history for the undo system.

---

# Libraries Used

## iostream

Used for:

* cin
* cout
* console interaction

```cpp
#include <iostream>
```

---

## string

Used for text handling.

```cpp
#include <string>
```

---

## stack

Used for the undo functionality.

```cpp
#include <stack>
```

---

## limits

Used for safe input handling.

```cpp
#include <limits>
```

This prevents invalid input issues.

Example:

```cpp
cin.ignore(numeric_limits<streamsize>::max(), '\n');
```

---

# Exception Handling

The system uses:

```cpp
try
catch
```

blocks to prevent crashes caused by invalid input.

Example:

```cpp
try {
    cin >> importance;
}
catch (exception& e) {
    cout << e.what();
}
```

---

# Algorithms Used

## Bubble Sort

Used for:

* Arrange by Importance
* Arrange by Due Date

### Time Complexity

| Case       | Complexity |
| ---------- | ---------- |
| Best Case  | O(n)       |
| Worst Case | O(n²)      |

---

# Linked List Operations

## Insertion

New tasks are inserted at the end of the linked list.

### Time Complexity

```text
O(n)
```

---

## Deletion

Highest priority task is searched and removed.

### Time Complexity

```text
O(n)
```

---

## Traversal

The program traverses the linked list to display tasks.

### Time Complexity

```text
O(n)
```

---

# Stack Operations

## Push

Stores actions into the undo stack.

```cpp
undoStack.push(action);
```

---

## Pop

Removes the latest action during undo.

```cpp
undoStack.pop();
```

---

# Sample Program Flow

```text
========== MY TASK MENU ==========
1. Add Task
2. Delete Highest Priority Task
3. Complete Task
4. Show Tasks
5. Arrange Tasks by Due Date
6. Arrange Tasks by Importance
7. Undo
8. Exit
```

---

# Example Output

```text
1. Finish Assignment
   Importance: 9
   Due Date : 2026-05-10
   Status   : Pending
```

---

# Safety Features

The system includes:

* Input validation
* Exception handling
* Buffer clearing
* Null pointer checking
* Empty list checking

These prevent:

* Program crashes
* Infinite input loops
* Invalid memory access

---

# Advantages of the System

* Simple console interface
* Dynamic memory usage
* Undo functionality
* Organized task sorting
* Demonstrates multiple DSA concepts
* Beginner-friendly implementation

---

# Limitations

* Data is not permanently saved
* Console-based only
* Uses Bubble Sort (not optimal for large data)
* No graphical interface

---

# Possible Future Improvements

Future upgrades may include:

* File handling
* Database integration
* GUI version
* Login system
* Search functionality
* Priority queue implementation
* Better sorting algorithms
* Deadline notifications

---

# Conclusion

The MyTask Manager System is a beginner-friendly C++ project that demonstrates how different Data Structures and Algorithms work together in a practical application.

It showcases:

* Linked Lists
* Stack operations
* Sorting algorithms
* Dynamic memory allocation
* Exception handling

while providing a functional task management experience.
