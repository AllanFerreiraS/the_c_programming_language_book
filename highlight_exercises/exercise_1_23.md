### 🧩 Exercise 1.23 — Remove Comments from C Code

**Description:**  
A program that removes comments from C source files (`.c` and `.h`).  
It handles both single-line (`//`) and multi-line (`/* ... */`) comments, while preserving strings, for example, `"Hello /* not a comment */"` remains untouched.

**Features:**
- Supports multiple input files.
- Command-line options for selective removal:
  - `-s` → remove only single-line comments.
  - `-m` → remove only multi-line comments.
  - `-sm` or `-ms` → remove both.
  - `-h` → show the manual.
- Automatically generates new files named `<filename>_new.c` or `<filename>_new.h`.

**Example Usage:**
```bash
./program file1.c file2.c
./program -s file.c
./program -m file.c
./program -sm file.c
```