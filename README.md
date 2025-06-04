# Personnel Manager

A simple Flask web app to manage personnel records using a C backend library (via ctypes).  
Features adding personnel, listing them with sorting by different attributes, and a clean interactive frontend.

---

## Features

- Add personnel records (Last Name, First Name, Middle Initial, Age, ID, Salary)
- View personnel list with sorting options: Name, Age, ID, Salary
- Uses a C backend (`libpersonnel.so`) for storing and sorting records via ctypes
- Responsive frontend with dynamic updates using JavaScript and fetch API

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
