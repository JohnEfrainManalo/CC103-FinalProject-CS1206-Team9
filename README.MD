# MyTask: Task Scheduler / To-Do Manager

## Problem Description
A lot people forget their tasks, especially when they're doing multiple deadlines and responsibilities. Our program solves that by letting the users store, sort, prioritize, and manage their tasks in one place — with an undo feature. This project demonstrates the practical implementation of fundamental Data Structures and Algorithms concepts.

* Linked Lists
* Stack Data Structure 
* Sorting Algorithms
* Exception Handling 
* Dynamic Memory Allocation

It allows users to: 

* Add tasks 
* Delete the highest priority task 
* Complete tasks 
* View tasks 
* Arrange tasks by importance 
* Arrange tasks by due date 
* Undo actions


---

## Data Structures Used

### Singly Linked List
Each task is a node that holds a name, an importance level, due date, and completion status. The nodes are connected through a `next` pointer, forming a chain.

We used Linked list instead of an array because it does not limit inputs, and also we don't know how many tasks the user will add ahead of time. The list grows and shrinks dynamically — no wasted memory, no fixed limit.

### Stack (`std::stack`)
Every action the user takes (add, delete, complete) gets recorded as an `Action` and pushed onto a stack. When the user hits undo, the top action gets popped and will reversed.

A stack fits naturally here because undo always reverses the *most recent* thing — which is exactly what LIFO (Last In, First Out) gives you.

---

## Algorithm Explanation

**Adding a task** — A new node is created and appended to the end of the linked list. The action is pushed to the undo stack.

**Deleting the highest priority task** — The list is traversed once, tracking which node has the highest importance value. That node gets unlinked and deleted. O(n).

**Completing a task** — The user picks a task number from the displayed list. The program walks to that position and flips `complete` to `true`.

**Sorting (Bubble Sort)** — Used for both "sort by importance" and "sort by due date":
- Walk through the list comparing adjacent nodes
- If they're out of order, swap their data fields
- Repeat until no swaps happen in a full pass

Dates are stored as `YYYY-MM-DD` strings, so string comparison works correctly for date ordering without needing a date library.

**Undo** —
- Undo an *add* → delete the last node in the list
- Undo a *delete* → re-create the node and prepend it to the front
- Undo a *complete* → find the task by name and set `complete` back to `false`

---

## Iterative vs. Recursive

All operations in this project are iterative (loops only, no recursion).

**Which is faster?** Iterative. Recursive traversal adds a function call to the call stack for every single node — same O(n) complexity, but with extra overhead. For a long list, recursion also risks a stack overflow. Loops don't have that problem.

**Which is easier to understand?** For linked list traversal, iteration is clearer. A `while (temp != nullptr)` loop reads exactly like "keep going until the end." Recursion requires mentally unwinding the call stack to follow what's happening, which adds unnecessary complexity for something this straightforward.

---

## Design Decisions

**Linked list over array** — Task count is unknown at runtime. Dynamic allocation made more sense than pre-sizing an array and hoping it's big enough.

**`std::stack` over a custom stack** — The standard library's stack is already reliable and tested. Writing our own would add code for no real benefit, since the linked list already demonstrates custom data structure implementation.

**Bubble Sort** — Simple to implement and easy to verify. For the size of task lists this program realistically handles, O(n²) isn't a practical problem. A fancier sort would be harder to read and harder to debug.

**Swapping data instead of relinking nodes during sort** — Relinking requires carefully updating `front`, tail, and prev pointers for every swap, which is error-prone. Swapping the four data fields inside nodes is simpler and produces the same result.

**YYYY-MM-DD date format** — Storing dates as strings in this format lets us sort them correctly using plain string comparison (`<` and `>`), no date parsing needed.

**Single-level undo only** — Each undo call reverses exactly one action. Clean and predictable. Redo wasn't in scope.

---

## Team Members

**Team 9 — Byte_Me_67**  
CC103 | CS1206 | 2nd Semester, AY 2025–2026  
Batangas State University – Alangilan Campus

| SR-Code | Name | Role |
|---------|------|------|
| 25-01444 | Jayawon, Althea Jayne I. | Researcher, Tester |
| 25-78190 | Manalo, John Efrain V. | Main Programmer, System Architect |
| 25-07803 | Mondragon, Leneth M. | Documenter, Designer |

---

## Acknowledgements

Thanks to our CC103 instructor: Ms. Fatima Marie P. Agdon for the lectures on linked lists, stacks, and sorting that this project is built on. And to each other — this was a team effort from proposal to final submission.

- Schrager, S., & Sadowski, E. (2016). *Getting More Done: Strategies to Increase Scholarly Productivity.* Journal of Graduate Medical Education, 8(1), 10–13. https://doi.org/10.4300/JGME-D-15-00165.1
