# Studies Using *The C Programming Language*



## 📚 About

This repository contains my personal solutions and study notes for exercises from the book *The C Programming Language* by Brian Kernighan and Dennis Ritchie.

The goal of this project is to document my progress as I learn and improve my skills in the C programming language.

---

## 🛠️ How to Run

Run the code `gcc` or any other C compiler. An example running the first exercise:

```bash
gcc -o exercise_1_1.c ex-1-1.c
./ex-1-1
```

---

## ✅ Progress

```markdown
## Progress

- [ ] Chapter 1 (In Progress...)
- [ ] Chapter 2
- [ ] Chapter 3
- [ ] Chapter 4
- [ ] Chapter 5
- [ ] Chapter 6
- [ ] Chapter 7
- [ ] Chapter 8
```


## 🌟 Highlighted Exercises

Here are some of the most interesting or challenging exercises I’ve completed so far.

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
