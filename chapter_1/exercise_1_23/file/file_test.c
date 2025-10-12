/*
 * annotated_demo.c
 *
 * A compact C program packed with comments to explain what's going on.
 * Demonstrates:
 *  - includes, macros, function prototypes
 *  - iterative and recursive functions
 *  - bubble sort on array
 *  - simple singly-linked list
 *  - writing output to a file
 *
 * Use this as a learning reference. It's intentionally verbose in comments.
 */

#include <stdio.h>   // printf, fprintf, FILE
#include <stdlib.h>  // malloc, free, rand, srand, EXIT_SUCCESS
#include <string.h>  // memset, memcpy
#include <time.h>    // time (for srand seed)

/* ---------- macros ---------- */
#define ARRAY_SIZE 10   /* default size for demo arrays */
#define MAX_LINE 256    /* max length for textual buffers */

/* ---------- types for linked list demo ---------- */

/* A simple node for a singly-linked list of integers. */
typedef struct Node {
    int value;           // stored integer value
    struct Node *next;   // pointer to the next node in the list (NULL = end)
} Node;

/* ---------- function prototypes ---------- */

/* Math examples */
long factorial_recursive(int n);        // recursive factorial: beware of large n
long factorial_iterative(int n);        // iterative factorial: safer for tail control

/* Sorting example */
void bubble_sort(int *arr, size_t n);   // in-place bubble sort (educational)

/* Linked list helpers */
Node *list_create_node(int v);          // allocate and init a node
void list_append(Node **head, int v);   // append to end (uses pointer to head)
void list_print(const Node *head);      // print list to stdout
void list_free(Node *head);             // free all nodes

/* Utility */
void fill_random_array(int *arr, size_t n, int max_value); // fill array with pseudo-random ints
int write_array_to_file(const char *filename, const int *arr, size_t n); // save array to a file

/* ---------- function implementations ---------- */

/* Recursive factorial:
 * This uses recursion directly. It is clear and concise but can hit stack limits for big n.
 * It returns -1 on invalid input (negative n).
 */
long factorial_recursive(int n) {
    if (n < 0) {
        return -1; /* invalid */
    }
    if (n == 0 || n == 1) {
        return 1; /* base case */
    }
    /* recursive step */
    return n * factorial_recursive(n - 1);
}

/* Iterative factorial:
 * Avoids deep recursion by looping. Better for larger n (still overflows long eventually).
 */
long factorial_iterative(int n) {
    if (n < 0) {
        return -1; /* invalid */
    }
    long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

/* Bubble sort:
 * Educational version: repeatedly swaps adjacent items that are out of order.
 * Complexity: O(n^2) time, O(1) extra space. Not used in production for big arrays,
 * but great for teaching and tracing.
 */
void bubble_sort(int *arr, size_t n) {
    if (arr == NULL || n < 2) return; // nothing to do

    // Outer loop: after k passes, last k elements are in position
    for (size_t pass = 0; pass < n - 1; ++pass) {
        int swapped = 0; // flag to detect early-exit
        // Inner loop: compare adjacent pairs
        for (size_t i = 0; i < n - 1 - pass; ++i) {
            if (arr[i] > arr[i + 1]) {
                // swap arr[i] and arr[i+1]
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) {
            // array already sorted; early exit is possible
            break;
        }
    }
}

/* Linked list node allocation helper */
Node *list_create_node(int v) {
    Node *p = (Node *)malloc(sizeof(Node));
    if (!p) {
        fprintf(stderr, "Memory allocation failed in list_create_node\n");
        return NULL;
    }
    p->value = v;
    p->next = NULL;
    return p;
}

/* Append value to end of list.
 * We accept Node **head so we can modify the head pointer if list was empty.
 */
void list_append(Node **head, int v) {
    if (!head) return;
    Node *newnode = list_create_node(v);
    if (!newnode) return;

    if (*head == NULL) {
        *head = newnode; // empty list: new node becomes head
        return;
    }

    // otherwise find tail
    Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newnode;
}

/* Print list to stdout as: [1 -> 2 -> 3] */
void list_print(const Node *head) {
    putchar('[');
    const Node *cur = head;
    while (cur) {
        printf("%d", cur->value);
        if (cur->next) printf(" -> ");
        cur = cur->next;
    }
    printf("]\n");
}

/* Free all nodes; safe if head==NULL */
void list_free(Node *head) {
    while (head) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

/* Fill an array with pseudo-random integers in [0, max_value] */
void fill_random_array(int *arr, size_t n, int max_value) {
    if (!arr) return;
    for (size_t i = 0; i < n; ++i) {
        arr[i] = rand() % (max_value + 1);
    }
}

/* Write an array of ints to a text file, one per line.
 * Returns 0 on success, non-zero on failure.
 */
int write_array_to_file(const char *filename, const int *arr, size_t n) {
    if (!filename || !arr) return -1;
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        return -1;
    }
    for (size_t i = 0; i < n; ++i) {
        if (fprintf(f, "%d\n", arr[i]) < 0) {
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 0;
}

/* ---------- main: demo runner ---------- */
int main(int argc, char *argv[]) {
    /* Seed the pseudo-random generator so the array differs each run.
     * Using time(NULL) is common for simple demos.
     */
    srand((unsigned int)time(NULL));

    /* Demonstrate factorials */
    int n = 6; // chosen small to avoid overflow
    printf("Factorial of %d (recursive): %ld\n", n, factorial_recursive(n));
    printf("Factorial of %d (iterative): %ld\n\n", n, factorial_iterative(n));

    /* Demonstrate array creation and bubble sort */
    int arr[ARRAY_SIZE];
    fill_random_array(arr, ARRAY_SIZE, 99); // numbers 0..99

    printf("Array before sort: ");
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", arr[i]); // inline printing with space
    }
    printf("\n");

    bubble_sort(arr, ARRAY_SIZE);

    printf("Array after sort : ");
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", arr[i]); // now sorted
    }
    printf("\n\n");

    /* Write sorted array to a file named 'sorted_numbers.txt' */
    if (write_array_to_file("sorted_numbers.txt", arr, ARRAY_SIZE) == 0) {
        printf("Saved sorted array to 'sorted_numbers.txt'.\n\n");
    } else {
        printf("Failed to save sorted array to file.\n\n");
    }

    /* Linked list demo:
     * - Append some values (taken from the sorted array),
     * - Print list,
     * - Free memory.
     */
    Node *head = NULL; /* start with empty list */

    // We'll append the first 5 elements of arr into the list
    for (size_t i = 0; i < 5 && i < ARRAY_SIZE; ++i) {
        list_append(&head, arr[i]);
    }

    printf("Linked list built from first 5 elements of the sorted array: ");
    list_print(head);

    /* Clean up memory */
    list_free(head);
    head = NULL; /* good practice after freeing */

    /* Small demonstration of command-line argument processing:
     * If the user passed an argument, echo it.
     */
    if (argc > 1) {
        printf("\nYou passed %d argument(s). First argument: %s\n", argc - 1, argv[1]);
    } else {
        printf("\nNo command-line arguments were passed. Try: ./annotated_demo hello\n");
    }

    /* Program exit */
    return EXIT_SUCCESS; /* indicates success to the shell */
}
