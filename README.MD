# MyTask: Task Scheduler / To-Do Manager

---

## Problem Description

People tend to forget tasks — especially when juggling multiple deadlines at once. Writing things down helps, but a plain list doesn't tell you what's most urgent or what's due soonest. MyTask solves that by letting users store, prioritize, sort, and manage their tasks in one place, with the option to undo any mistake.

---

## Data Structures Used

### Singly Linked List

A linked list is a chain of nodes where each node holds its own data and a pointer to the next node. Unlike an array, the nodes don't have to sit next to each other in memory — they just know where the next one is.

In MyTask, each node is one task. It stores the task name, importance level, due date, completion status, and a `next` pointer that connects it to the task after it. The `front` pointer (a private member of `TaskManager`) marks the start of the chain.

We chose a linked list over an array because we have no idea how many tasks a user will add. An array would force us to pick a fixed size upfront. With a linked list, the program grows or shrinks on demand — no wasted space, no hard limit.

### Stack (`std::stack`)

A stack is a data structure where you can only interact with the top. The rule is LIFO — Last In, First Out. Think of a stack of plates: the last plate placed is the first one taken.

In MyTask, every action (add, delete, complete) gets recorded as an `Action` object and pushed onto `undoStack`. When the user chooses Undo, the program pops the top record and reverses it.

A stack is the right fit here because undo always reverses the *most recent* action — which is exactly what LIFO gives you, without any extra bookkeeping.

### Class (`TaskManager`)

All data and functions are organized inside a `TaskManager` class. `front`, `undoStack`, and `taskIDCounter` are private members, meaning nothing outside the class can directly touch them. The class also has a destructor (`~TaskManager`) that automatically walks the linked list and frees every node when the program exits — so there are no memory leaks.

We chose a class over loose global variables because it groups everything that belongs together in one place, protects the internal state from accidental modification, and makes the structure of the program cleaner and easier to follow.

---

## Algorithm Explanation

**Adding a task**
- Allocate a new node on the heap using `new`
- Fill in its fields (task name, importance, due date, complete = false)
- If the list is empty, the new node becomes `front`
- Otherwise, walk from `front` to the last node and attach the new node there
- Push an `ADD_ACTION` record onto the undo stack

**Deleting a task**
- Display the current task list so the user can see position numbers
- Walk the list using two pointers: `temp` at the target node, `prev` one step behind
- Save the action to the undo stack (with a full data backup) *before* deleting
- Bypass the node by making `prev->next` point to `temp->next`
- Call `delete temp` to free the memory

**Completing a task**
- Display the list, user picks a position number
- Walk to that position with a single pointer
- Push a `COMPLETE_ACTION` record onto the undo stack
- Set `temp->complete = true`

**Displaying tasks (Recursive)**
- On the first call, `temp` starts at `front`
- Print the current node's task name, importance, due date, and status
- Call `showTasks(temp->next, counter + 1)` to move to the next node
- When `temp` reaches `nullptr` (end of the list), the function returns — this is the base case

**Sorting — Bubble Sort**
Used for both sort-by-importance and sort-by-due-date:
- Walk through the list, comparing each adjacent pair of nodes
- If they're out of order, swap all five data fields between them (id, task, importance, dueDate, complete)
- Track whether any swap happened in this pass using a `swapped` flag
- Repeat until a full pass makes zero swaps — the list is sorted

Dates are stored as `YYYY-MM-DD` strings, so standard string comparison (`<` and `>`) naturally produces the correct date order without needing any date library.

**Undo**
- Undo an *add* → find the added node by its saved pointer, unlink and delete it
- Undo a *delete* → create a new node from the saved data backup, reinsert it at its original position using the saved `prev` pointer
- Undo a *complete* → directly set the node's `complete` field back to `false`

---

## Iterative vs. Recursive

Most operations in this project are iterative — but `showTasks()` is recursive.

**Recursive — `showTasks()`**
The function prints the current node, then calls itself with the next node. The base case is when `temp == nullptr`, meaning the end of the list has been reached. Each call handles exactly one node and passes the rest down.

**Iterative — everything else**
`addTask`, `delete_Task`, `completeTask`, and both sort functions all use `while` loops to walk the list.

**Which is faster?** Iterative. Recursive calls add a new frame to the call stack for every single node — same O(n) steps, but with more overhead per step. On a very long list, recursion also risks a stack overflow. Loops don't have that problem.

**Which is easier to understand?** It depends on the situation. For `showTasks`, recursion is actually quite readable — each call handles one task and moves on, which mirrors how you'd think about the problem naturally. For operations like delete or sort where you need two pointers and careful control, iteration is clearer.

---

## Design Decisions

**Class over global variables** — The original version used global variables for `front`, `undoStack`, and `taskIDCounter`. Wrapping them in a `TaskManager` class keeps the internal state protected and groups related data and functions together. The destructor also ensures all heap memory is properly cleaned up when the program exits.

**Linked list over array** — Task count is unknown at runtime. Dynamic allocation made more sense than pre-sizing an array and guessing a limit.

**`std::stack` over a custom stack** — The standard library's stack is already reliable and well-tested. Writing our own would add code with no real payoff, since the linked list already demonstrates building a custom data structure from scratch.

**Recursive `showTasks()`** — Displaying tasks is a naturally recursive problem: show the current node, then show the rest of the list. The recursive version is clean and readable for this purpose. The risk of stack overflow is not a concern for a personal task list.

**Bubble Sort** — Straightforward to implement and easy to trace through mentally. For the realistic size of a personal task list, the O(n²) performance isn't a problem. A faster algorithm like Merge Sort would be harder to read and harder to debug for what we're building here.

**Swapping data instead of relinking nodes during sort** — Relinking would mean carefully updating `front`, previous-node pointers, and next-node pointers for every swap — easy to get wrong. Swapping the five data fields inside two adjacent nodes is simpler and gives the same result.

**YYYY-MM-DD date format** — This format lets us sort dates correctly using plain string comparison. `"2025-06-01" < "2025-12-01"` is true, and that's all we need — no date parsing, no extra library.

**Single-level undo only** — Each undo call reverses exactly one action. Clean and predictable. Redo was outside the scope of this project.

---

## Team Members

**Team 9 — Byte_Me_67**  
CC103 | CS1206 | 2nd Semester, AY 2025–2026  
Batangas State University – Alangilan Campus

| SR-Code | Name | Role |
|---------|------|------|
| 25-01444 | Jayawon, Althea Jayne I. | Praogrammer, Documenter |
| 25-78190 | Manalo, John Efrain V. | Main Programmer, System Architect |
| 25-07803 | Mondragon, Leneth M. | Programmer, Tester |

---

## Acknowledgements

Thanks to our CC103 instructor, Ms. Fatima Marie P. Agdon, for the lectures on linked lists, stacks, and sorting that this project is built on. And to each other — this was a full team effort from proposal to final submission.

- Schrager, S., & Sadowski, E. (2016). *Getting More Done: Strategies to Increase Scholarly Productivity.* Journal of Graduate Medical Education, 8(1), 10–13. https://doi.org/10.4300/JGME-D-15-00165.1
