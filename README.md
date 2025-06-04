# Personnel Manager

A web-based personnel management system using a Flask frontend and a C backend.  
Records are stored and sorted in binary trees and doubly-linked lists, all handled in C for speed and structure.

---

## Features

- Add personnel records with: Last Name, First Name, Middle Initial, Age, ID, Salary
- Store records in multiple binary search trees (sorted by: name, age, ID, salary)
- Convert trees into a doubly-linked list for navigation
- Print records sorted in various orders
- View and sort records through a Flask web UI

---

## C Backend Design

The C code handles data storage and sorting efficiently using trees and lists:

- `PERSONNEL_REC`: struct representing each person
- Binary search trees (`NODE*`) for sorting by:
  - Name
  - Age
  - ID
  - Salary
- `insert_personnel_record(...)`: inserts a record into a tree with custom comparator
- Comparators:
  - `compare_name`
  - `compare_age`
  - `compare_id_number`
  - `compare_salary`
- In-order traversal (`traverse_and_print_records`) for sorted output
- Tree → Doubly-linked list conversion (`insert_from_tree_into_list`)
- Print records:
  - Forward / Backward traversal
  - First `n` records via wraparound

---

## Stack

- **Frontend:** HTML + CSS + JS (fetch API)
- **Backend:** Python Flask server with C backend via `ctypes`
- **C Structures:** BST and doubly-linked list

---

## Getting Started

### Prerequisites

- Python 3.x
- Flask
- A compiled shared C library `libpersonnel.so` that implements personnel record storage and sorting
- `personnel` executable (optional, if used for adding records via subprocess)

### Install dependencies

```bash
pip install flask
```

3. Start the server:
```bash
python app.py
```

4. Open in browser: http://localhost:5000

🔗 See More
Visit [my website](https://ganaa.work) for more projects and demos.
