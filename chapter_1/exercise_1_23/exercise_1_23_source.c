#include "exercise_1_23_source.h"


// FILES
ex23_file original_file;
ex23_file temp_file;
ex23_file new_file;




// Function to check if char array in less than 256 characters
char chararr_in_sizenum(char * arr, int size) {
    int i = 0;
    while (arr[i] != '\0' && arr[i] != '\n') {
        ++i;
    }

    if (i < MAXCHARPATH)
        return TRUE;
    return FALSE;
}


// Function to open a new file and attribute the new body to file.body = * FILE.
char open_file(char * path, char * mode, FILE ** f) {

    FILE * file_test = NULL;
    file_test = fopen(path, mode);
    if (file_test == NULL) {
        return EXIT_FAILURE;
    }

    *f = file_test;
    return EXIT_SUCCESS;
}

// Function to rename a file to <name>_new.c
char * generate_name_new_dot_c(ex23_file f) {
    
    // _new.c
    int name_new_char_count = 6;
    // Size of the path of original file
    int name_size = 0;
    // Index
    int index = 0;

    if (f.body == NULL) {
        printf("%s >> Não foi possível gerar novo nome, arquivo no caminho \'%s\' está definido como NULL\n.", ERRORMESSAGE, f.path);
        return NULL;
    }

    char * name_new = (char *) malloc(MAXCHARPATH);
    
    if (name_new == NULL) {
        printf("%s >> Não foi possível gerar novo nome, ocorreu um erro ao alocar memória.\n", ERRORMESSAGE);
        return NULL;
    }

    // Cleaning the new Array
    for (int i = 0; i < MAXCHARPATH; i++) {
        name_new[i] = '\0';
    }

    // Count the chars in the original name
    for (name_size = 0; f.path[name_size] != '\0'; name_size++) { /*Nothing*/ }

    while ((index + name_new_char_count) < MAXCHARPATH - 1) {
        
        if (f.path[index] == '\0' || index == (name_size - 2)) {
            break;
        }
        name_new[index] = f.path[index];
        index++;
    }
    name_new[index] = '_';
    name_new[++index] = 'n';
    name_new[++index] = 'e';
    name_new[++index] = 'w';
    name_new[++index] = '.';
    name_new[++index] = f.path[name_size - 1];

    return name_new;
}

// Function to find a file in a path and saving it in the ex23_file structure
char select_file(char * path) {

    if ( !chararr_in_sizenum(path, MAXCHARPATH) ) {
        printf("%s >> O caminho %s excedeu o limite de %d caracteres!\n", ERRORMESSAGE, path, MAXCHARPATH);
        return EXIT_FAILURE;
    }

    if ( open_file(path, "r", &original_file.body) ) { // Caso ocorra um erro
        printf("%s >> Não foi possível abrir o arquivo que se encontra no caminho \'%s\'\n", ERRORMESSAGE, path);
        return EXIT_FAILURE;
    }
    original_file.path = path;
    original_file.temp = FALSE;
    return EXIT_SUCCESS;
}

// Function to create a new file and add it to ex23_file.
char create_file(char * name, char * path, char temp, ex23_file * ptr_file) {

    if ( !chararr_in_sizenum(path, MAXCHARPATH) ) {
        printf("%s >> O caminho %s excedeu o limite de %d caracteres!\n", ERRORMESSAGE, path, MAXCHARPATH);
        return EXIT_FAILURE;
    }

    if ( open_file(path, "w", &ptr_file->body) ) { // Caso ocorra um erro
        printf("%s >> Não foi possível criar o arquivo '%s' que se encontra no caminho '%s'.\n", ERRORMESSAGE, name, path);
        return EXIT_FAILURE;
    }
    
    ptr_file->name = name;
    ptr_file->path = path;
    ptr_file->temp = temp;
    return EXIT_SUCCESS;
}


// Function to copy the content of a file to other
// from must be in read mode, to must be in write mode.
char copy_file_to_file(ex23_file * from, ex23_file * to) {
    
    if (from->body == NULL || to->body == NULL) {
        printf("%s >> Não foi possivel fazer a copia do arquivo \'%s\' para \'%s\'. Ponteiro está apontando para NULL\n", ERRORMESSAGE, from->path, to->path);
        return EXIT_FAILURE;
    }
    
    char line_read[MAXCHARARRAY] = {0};
    // Reading the array of chars in the file
    while ( fgets(line_read, MAXCHARARRAY, from->body) != NULL) {
        // printf("%s", line_read);

        // getting each char of the array
        int index = 0;
        while (line_read[index] != '\0') {
            fputc(line_read[index], to->body);
            index++;
        }
    }

    return EXIT_SUCCESS;
}

// The function closes the file and make file.body = NULL;
char close_ex23_body(ex23_file * f) {
    
    f->name = NULL;

    if ( f->body != NULL) {
        if ( fclose(f->body) != 0 ) {
            printf("%s >> Não foi possível fechar o arquivo '%s'.\n", ERRORMESSAGE, f->name);
            return EXIT_FAILURE;
        }

        f->body = NULL;
    }
    return EXIT_SUCCESS;
}

// The function closes the file and open it again with the new mode.
char change_file_mode(ex23_file * f, char * mode) {

    if ( close_ex23_body(f) ) // If EXIT_FAILURE
        return EXIT_FAILURE;
    if ( open_file(f->path, mode, &f->body) ) { // If EXIT_FAILURE
        printf("%s >> Erro ao tentar mudar o modo do arquivo para \"%s\".\n", ERRORMESSAGE, mode);
        printf("%s >> Não foi possível reabrir o arquivo que se encontra no caminho %s.\n", ERRORMESSAGE, f->path);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Function
// 'from'(temp) file mode:  r
// 'to'(new) file mode:    w
// Step 1: reverse the modes: (from w) (to  r) -> Now 'from' is empty
// Step 2: copy of 'from' to 'to'
// Step 3: reverse the modes: (from r) (to w) -> Now 'to' is empty
char save_changes(ex23_file * from, ex23_file * to) {
    
    // Step 1
    if ( change_file_mode(to, "r") ) // If error
        return EXIT_FAILURE;
    if ( change_file_mode(from, "w") ) // If error
        return EXIT_FAILURE;
    
    // Step 2
    if ( copy_file_to_file(to, from) )
        return EXIT_FAILURE;

    // Step 3
    if ( change_file_mode(from, "r") )
        return EXIT_FAILURE;
    if ( change_file_mode(to, "w") )
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}


// Function that removes all single line comments from a file.
char remove_singleline_comments(ex23_file * from, ex23_file * to) {

    if (from->body == NULL || to->body == NULL) {
        printf("%s >> Não foi possivel remover comentarios simples. Ponteiro do arquivo de origem/destino está apontando para NULL\n", ERRORMESSAGE);
        return EXIT_FAILURE;
    }

    char line_read[MAXCHARARRAY] = {0};
    char word_char = '\0';
    char special_char = 0;
    // If 2, then '//'
    int flag_char_counter = 0;
    int i = 0;

    while ( fgets(line_read, MAXCHARARRAY, from->body) != NULL) {
        
        i = 0;

        while (line_read[i] != '\0') {

            if (flag_char_counter < 2) {

                // Check if current string reading is outside or inside "" or ''.

                if (line_read[i] == '\\') {
                    special_char = 1;
                }
                else if (special_char == 1 && (line_read[i] == '\'' || line_read[i] == '\"')) {
                    special_char = 0;
                }
                else if ((line_read[i] == '\"' || line_read[i] == '\'') && word_char == '\0' && special_char == 0) {
                    word_char = line_read[i];
                }
                else if ((line_read[i] == '\"' || line_read[i] == '\'') && word_char == line_read[i] && special_char == 0) {
                    word_char = '\0';
                }

                if ((line_read[i] != '/') || (line_read[i] == '/' && word_char != '\0')) {
                    if (flag_char_counter == 1) {
                        //printf("/");
                        fputc('/', to->body);
                    }
                    flag_char_counter = 0;
                    //printf("%c", line_read[i]);
                    fputc(line_read[i], to->body);
                }
                else if ( line_read[i] == '/' && word_char == '\0')
                    flag_char_counter++;
            }
            else if (flag_char_counter >= 2 && line_read[i] == '\n') {
                //printf("%c", line_read[i]);
                fputc(line_read[i], to->body);
            }

            if (line_read[i] == '\n') {
                flag_char_counter = 0;
                special_char = 0;
                word_char = '\0';
            }
            i++;
        }
    }

    return EXIT_SUCCESS;
}


// Function that removes all multiline comments from a file.
char remove_multiline_comments(ex23_file * from, ex23_file * to) {

    if (from->body == NULL || to->body == NULL) {
        printf("%s >> Não foi possivel remover comentarios simples. Ponteiro do arquivo de origem/destino está apontando para NULL\n", ERRORMESSAGE);
        return EXIT_FAILURE;
    }

    // Buffer
    char line_read[MAXCHARARRAY] = {0};
    // /*
    char flag_char_counter[2] = {'\0', '\0'};
    // Store / and *
    char char_buffer = '\0';
    // char '\'
    char special_char = 0;
    // Is between strings
    char word_char = '\0';
    // Counter
    int i = 0;

    while ( fgets(line_read, MAXCHARARRAY, from->body) != NULL) {

        i = 0;

        while (line_read[i] != '\0') {
            
            if (flag_char_counter[1] == '\0') {

                if (line_read[i] == '\\') {
                    special_char = 1;
                }

                if ((line_read[i] == '\'' || line_read[i] == '\"') && word_char == '\0' && special_char == 0) {
                    word_char = line_read[i];
                }
                else if ((line_read[i] == '\'' || line_read[i] == '\"') && word_char == line_read[i] && special_char == 0) {
                    word_char = '\0';
                }
                else if (line_read[i] != '\\' && special_char == 1) {
                    special_char = 0;
                }

                // Trying to open /*
                if (line_read[i] == '/' && flag_char_counter[0] == '\0' && word_char == '\0') {
                    char_buffer = line_read[i];
                    flag_char_counter[0] = line_read[i];
                }
                else if (line_read[i] == '*' && flag_char_counter[0] != '\0' && flag_char_counter[1] == '\0' && word_char == '\0') {
                    char_buffer = '\0';
                    flag_char_counter[1] = line_read[i];
                }
                else {
                    flag_char_counter[0] = '\0';
                    flag_char_counter[1] = '\0';
                    if (char_buffer != '\0') {
                        fputc(char_buffer, to->body);
                        char_buffer = '\0';
                    }
                    fputc(line_read[i], to->body);
                }
            }
            else {
                
                // Trying to close */
                if (line_read[i] == flag_char_counter[1]) {
                    char_buffer = line_read[i];
                }
                else if (line_read[i] == flag_char_counter[0] && char_buffer == flag_char_counter[1]) {
                    char_buffer = '\0';
                    flag_char_counter[0] = '\0';
                    flag_char_counter[1] = '\0';
                }
                else if (char_buffer != '\0') {
                    char_buffer = '\0';
                }
            }
            i++;
        }
    }

    return EXIT_SUCCESS;
}

// Function to delete a file using ex23_file as parameter
void delete_file(ex23_file * f) {
    
    char * file_path = f->path;
    if ( remove(file_path) != 0 ) {
        printf("%s >> Não foi possível excluir o arquivo \'%s\'. Apenas ignore ou exclua-o manualmente.\n", ERRORMESSAGE, file_path);
    }
}

void man_program() {
    printf("%s >> Entrando no modo manual.\n", NORMALMESSAGE);
    printf("\n");
    printf("Sintax:\n");
    printf("exercise_1_23 [opções] arquivo1.c [arquivo2.c ...]\n");
    printf("\nDescrição:\n");
    printf("Remove comentários de arquivos com extensão .c e .h.\nCada arquivo processado gera uma nova versão sem comentários, com o sufixo _new no nome.\n");
    printf("-s\t\tRemove apenas comentários de linha simples (//)\n");
    printf("-m\t\tRemove apenas comentários de múltiplas linhas (/* ... */)\n");
    printf("-h\t\tExibe este manual de ajuda\n");
    printf("\nExemplos:\n");
    printf("exercise_1_23 file1.c file2.c\n");
    printf("Remove todos os tipos de comentários dos arquivos file1.c e file2.c, gerando file1_new.c e file2_new.c.\n\n");
    printf("exercise_1_23 -s file1.c\n");
    printf("Remove apenas comentários de linha simples do arquivo file1.c, gerando file1_new.c.\n\n");
    printf("exercise_1_23 -m file1.c file2.c\n");
    printf("Remove apenas comentários de múltiplas linhas dos arquivos indicados.\n\n");
    printf("exercise_1_23 -sm file.c\exercise_1_23 -ms file.c\n");
    printf("Ambos removem todos os tipos de comentários do arquivo file.c.\n");
    printf("\n");
    printf("%s >> Saindo do modo manual.\n", NORMALMESSAGE);
}