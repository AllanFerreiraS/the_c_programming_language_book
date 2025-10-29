### 🧩 Exercise 1.24 — Check C Program for Basic Syntax Errors

**Description:**  
A program that checks C source files (`.c` and `.h`) for rudimentary syntax errors, such as unmatched parentheses `()`, brackets `[]`, and braces `{}`.  
It also correctly handles:
- Single and double quotes.
- Escape sequences (e.g., `\"`, `\\`).
- Comments (both `//` and `/* ... */`).

**Usage:**
  - `-h`, `--help` → Show this help message and exit.

**Example Usage:**
```bash
./syntax_checker file.c
./syntax_checker file1.c file2.c
./syntax_checker -h
./syntax_checker --help