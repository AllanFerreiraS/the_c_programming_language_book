

#include "exercise_1_24.h"


// VARS
short command_char_counter = 0;
short singleline_char_counter = 0;
short multiple_char_counter = 0;
char char_word = '\0';




// Function to check if char array in less than size characters
char chararr_in_sizenum(char * arr, int size, int * real_size) {
    int i = 0;
    while (arr[i] != '\0' && arr[i] != '\n') {
        ++i;
    }

    *real_size = i;

    if (i < size)
        return TRUE;
    return FALSE;
}

// Function to open a new file and attribute the new body to file.body = * FILE.
char open_file(char * path, ex24_file * file) {

    file->body = fopen(path, "r");
    if (file->body == NULL) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// Function to open a file and attribute the new body to file.body and it's path.
char select_file(char * path, ex24_file * file) {

    if ( !chararr_in_sizenum(path, MAXCHARARRAY, &file->path_size) ) {
        printf("%s >> O caminho \'%s\' excedeu o limite de %d caracteres! Número de caracteres atual: %d.\n", ERRORMESSAGE, path, MAXCHARARRAY - 1, file->path_size);
        return EXIT_FAILURE;
    }

    if ( open_file(path, file) ) { // Caso ocorra um erro
        printf("%s >> Não foi possível abrir o arquivo que se encontra no caminho \'%s\'.\n", ERRORMESSAGE, path);
        return EXIT_FAILURE;
    }
    
    file->path = path;

    // Chamar função para pegar somente o nome do arquivo.extensão

    return EXIT_SUCCESS;
}

// The function closes the file;
char close_file(ex24_file * file) {
    
    file->name = NULL;
    file->path = NULL;
    file->path_size = 0;

    if ( file->body != NULL) {
        if ( fclose(file->body) != 0 ) {
            printf("%s >> Não foi possível fechar o arquivo '%s'.\n", ERRORMESSAGE, file->name);
            return EXIT_FAILURE;
        }

        file->body = NULL;
    }
    return EXIT_SUCCESS;
}

// Read File char by char
char read_file(ex24_file * file, char ** feedback) {

    if (file->body == NULL) {
        printf("%s >> Não foi possivel ler o arquivo \'%s\'. Ponteiro do arquivo está apontando para NULL.\n", ERRORMESSAGE, file->path);
        return EXIT_FAILURE;
    }

    // Stack
    stack * t = stack_new();

    if ( t == NULL ) {
        printf("%s >> Erro ao alocar memoria para o Stack.\n", ERRORMESSAGE);
        return EXIT_FAILURE;
    }

    // Variables
    int index =                     0;
    char buffer[MAXCHARARRAY] =     {0};
    char in_a_word =                FALSE;
    char in_a_scape_sequence =      FALSE;
    char in_a_singlecomment =       FALSE;
    char in_a_multiplecomment =     FALSE;

    char * fdbk = (char * ) malloc( sizeof(char) * 101 ); // Feedback
    unsigned int line_counter = 1;

    if (fdbk == NULL) {
        printf("%s >> Erro ao alocar memoria.\n", ERRORMESSAGE);
        return EXIT_FAILURE;
    }

    // Read file
    while ( fgets(buffer, MAXCHARARRAY, file->body) != NULL ) {

        index = 0;

        // Read current buffer
        while (buffer[index] != '\0') {

            // Line Counter
            if (buffer[index] == '\n')
                line_counter++;

            // check if current buffer is in a single comment
            if (! in_a_word)
                in_singlecomment(buffer[index], &singleline_char_counter, &in_a_singlecomment);
            
            // Check if current buffer is in a single comment
            if (! in_a_word)
                in_multiplecomment(buffer[index], &multiple_char_counter, &in_a_multiplecomment);

            // Check if current buffer is in a word '' or ""
            if (! in_a_singlecomment)
                if (! in_a_multiplecomment)
                    in_word(buffer[index], &command_char_counter, &char_word, &in_a_word);

            if (in_a_word) {
                // Check if current buffer is a scape sequence
                in_scape_sequence(buffer[index], &command_char_counter, &in_a_scape_sequence);
            }

            // Check if ([{}]) are closed correctly
            if (! in_a_word)
                if (! in_a_singlecomment)
                    if (! in_a_multiplecomment)
                        if ( open_close_check(buffer[index], &t, line_counter) ) { // If Error
                            snprintf(fdbk, 101, ">> [%s Error]: On line %d:\n\t\tThe char \'%c\' is closed without a opening.\n", file->path, 
                                stack_return_line_number(t), buffer[index]);
                            *feedback = fdbk;
                            stack_erase(&t);
                            return EXIT_SUCCESS; // "SUCCESS... HA"
                        }

            index++;
        }
    }
    
    // Check if there is a string opened
    if (in_a_word) {
        snprintf(fdbk, 101, ">> [%s Error]:\n\t\tThere is/are quote(s) still opened.\n", file->path);
        *feedback = fdbk;
        stack_erase(&t);
        return EXIT_SUCCESS; // "SUCCESS... HA"
    }

    // Check if multiline comment is still opened
    if (in_a_multiplecomment) {
        snprintf(fdbk, 101, ">> [%s Error]:\n\t\tFile ended, but a multiline comment was not properly closed.\n", file->path);
        *feedback = fdbk;
        stack_erase(&t);
        return EXIT_SUCCESS; // "SUCCESS... HA"
    }

       // Check if stack is empty or not
    if ( ! (stack_is_end(t) && stack_return_data(t) == '\0') ) {
        snprintf(fdbk, 101, ">> [%s Error]: On line %d:\n\t\tThe char \'%c\' is opened, but it is not closed.\n", file->path, 
            stack_return_line_number(t), stack_return_data(t));
        *feedback = fdbk;
        stack_erase(&t);
        return EXIT_SUCCESS; // "SUCCESS... HA"
    }

    snprintf(fdbk, 101, ">> [%s SUCCESS]\n", file->path);
    *feedback = fdbk;

    stack_erase(&t);

    return EXIT_SUCCESS;
}

char open_close_check(char buffer, stack ** pStack, unsigned int line) {

    if ( buffer == '(' || buffer == '[' || buffer == '{') {
        stack_push(pStack, buffer, line);
    }
    else if ( buffer == ')' || buffer == ']' || buffer == '}') {

        if ( stack_return_data(*pStack) == '(' && buffer == ')' )
            stack_pop(pStack);
        else if ( stack_return_data(*pStack) == '[' && buffer == ']' )
            stack_pop(pStack);
        else if ( stack_return_data(*pStack) == '{' && buffer == '}' )
            stack_pop(pStack);
        else {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

// Function to check if current buffer is part of a string '' or "".
// ccc: Comand Char Counter
// return value to param 'result'
void in_word(char buffer, short * ccc, char * char_word, char * result) {

    // Not changing
    if ( (buffer != '\'' && buffer != '\"') && (*char_word) == '\0') {
        *result = FALSE;
        return;
    }
    if ( (buffer != '\'' && buffer != '\"') && (*char_word) != '\0') {
        *result = TRUE;
        return;
    }

    // Changing
    if ( (buffer == '\'' || buffer == '\"') && (*ccc) == 0 && (*char_word) == '\0') {
        *char_word = buffer;
        *result = TRUE;

        return;
    }
    if ((buffer == '\'' || buffer == '\"') && (*ccc) == 0 && (*char_word) == buffer) {
        *char_word = '\0';
        *result = FALSE;

        return;
    }
    else {
        *result = TRUE;
        return;
    }
}

// Function to check if current buffer is part of a scape sequence.
// ccc: Comand Char Counter
// return value to param 'result'
void in_scape_sequence(char buffer, short * ccc, char * result) {

    if ( buffer == '\\' && (*ccc) == 0 ) {
        (*ccc) += 1;
        *result = TRUE;
        return;

    }
    if ( (*ccc) >= 1 ) {
        (*ccc) = 0;
        *result = FALSE;
        return;

    }

}

// Function to check if current buffer is part of a single line comment.
// scc: Singleline Char Counter
// return value to param 'result'
void in_singlecomment(char buffer, short * scc, char * result) {

    if ( buffer == '/' )
        (*scc) += 1;


    if (*scc < 2 && buffer != '/') {
        *scc = 0;
        *result = FALSE;
        return;
    }
    else if ( *scc >= 2 && buffer != '\n' ) {
        *result = TRUE;
        return;
    }
    else if ( *scc >= 2 && buffer == '\n' ) {
        *scc = 0;
        *result = FALSE;
        return;
    }
}

// Function to check if current buffer is part of a multiple line comment.
// mcc: Multipleline Char Counter
// return value to param 'result'
void in_multiplecomment(char buffer, short * mcc, char * result) {

    // Opening it
    if ( buffer == '/' && (*mcc) == 0 && (*result) == FALSE ) {
        (*mcc) += 1;
        return;
    }

    if ( buffer == '*' && (*mcc) == 1 && (*result) == FALSE ) {
        (*mcc) += 1;
        *result = TRUE;
        return;
    }
    
    // Closing it
    if (buffer == '*' && (*mcc) == 2 && (*result) == TRUE ) {
        (*mcc) -= 1;
        return;
    }

    if (buffer == '/' && (*mcc) == 1 && (*result) == TRUE ) {
        (*mcc) -= 1;
        *result = FALSE;
        return;
    }
    
    if (*mcc < 2){

        if (*result == TRUE && buffer != '*')
            (*mcc) = 2;
        else if (*result == FALSE) {
            (*mcc) = 0;
        }
        return;
    }
    
}

void restart_vars() {

    // VARS
    command_char_counter = 0;
    singleline_char_counter = 0;
    multiple_char_counter = 0;
    char_word = '\0';
}

void print_help(void) {
    printf("\nC Syntax Checker - Exercise 1-24\n");
    printf("Usage:\n");
    printf("  ./main [options] <file1> <file2> ...\n\n");
    printf("Options:\n");
    printf("  -h, --help       Show this help message and exit\n\n");
    printf("Description:\n");
    printf("  Checks C source files for rudimentary syntax errors:\n");
    printf("    - unmatched parentheses '()', brackets '[]', and braces '{}'\n");
    printf("    - unclosed single or double quotes\n");
    printf("    - unclosed single-line '//' or multi-line '/* */' comments\n\n");
    printf("Example:\n");
    printf("  ./main file1.c file2.c file3.c\n\n");
}
