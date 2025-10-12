/*
Write a program to remove all comments from a C program.
Don't forget to handle quoted strings and character constants properly.
C comments don't nest.
*/

/*
    PROCESSOS:
    [0] Verificar caminhos de arquivos passados como parametro para o main. (X)
    [1] Gerar um arquivo temp para ser usado como um buffer.                (X)
    [2] original.c -> copia -> .temp.c                                      (X)
    [3] .temp.c -> [processos] -> novo.c                                    (x)
    [4] novo.c -> copia -> .temp.c                                          (x)
    [5] passo 3 e 4 repetem até todo o processo ser finalizado.             ()
    PS: .temp.c deve ser igual ao novo.c para não haver conflitos.
*/

/*
    FEATURES:
    1: Poder passar mais de um arquivo como parâmetro para o main.
    2: Parametro para salvar mudanças no arquivo original.
    3: Parametros para escolher remover somente '//' ou comentarios de mais de uma linha.
*/

#include <stdio.h>
#include "exercise_1_23_source.h"

char feedback;
char commands[AMOUNTCOMMAND + 1] = {0};

int main(int argc, char **argv) {
    
    if (argc <= 1) {
        printf("%s >> O programa deve conter pelo menos 1 caminho para o arquivo a ser modificado.\n", ERRORMESSAGE);
        return EXIT_FAILURE;
    }

    // If the first parameter is a command
    if (argv[1][0] == '-') {
        for (int i = 0; argv[1][i+1] != '\0'; i++) {
            if (i < AMOUNTCOMMAND) {
                commands[i] = argv[1][i+1];
            }
        }
    }

    // Check if there is a unkown command
    if (commands[0] != 0) {
        for (int i = 0; i < AMOUNTCOMMAND; i++) {
            if (commands[i] != 's' && commands[i] != 'm' && commands[i] != 'h' && commands[i] != 0) {
                printf("%s >> O comando \'%c\' não é reconhecido pelo programa.\n", ERRORMESSAGE, commands[i]);
                return EXIT_FAILURE;
            }
        }
    }

    // Check if there is the -h command
    for (int i = 0; i < AMOUNTCOMMAND; i++) {
        if (commands[i] == 'h') {
            man_program();
            return EXIT_SUCCESS;
        }
    }

    // If there is a command, it will search for files at the next argv index
    int j = 1;
    if (commands[0] != 0)
        j++;

    // Check if a command was give, but no files
    if (j == argc) {
        printf("%s >> O programa deve conter pelo menos 1 caminho para o arquivo a ser modificado.\n", ERRORMESSAGE);
        return EXIT_FAILURE;
    }

    feedback = create_file(".temp.c", ".temp.c", TRUE, &temp_file);
    if (feedback)
        return EXIT_FAILURE;


    // The whole program
    for (; j < argc; j++) {

        feedback = select_file(argv[j]);
        if (feedback && (j + 1) < argc) {
            printf("%s >> Procurando próximo arquivo...\n", NORMALMESSAGE);
            continue;
        }
        if (!feedback) {

            printf("%s >> O arquivo \'%s\' foi selecionado.\n", SUCCESSMESSAGE, original_file.path);

            char * new_name = NULL;
            new_name = generate_name_new_dot_c(original_file);

            // Copy original content to .temp.c before start making changes.
            feedback = copy_file_to_file(&original_file, &temp_file);
            if (feedback)
                return EXIT_FAILURE;

            // Close original file.    
            feedback = close_ex23_body(&original_file);
            if (feedback)
                return EXIT_FAILURE;

            // Change .temp.c from write to read mode.
            feedback = change_file_mode(&temp_file, "r");
            if (feedback)
                return EXIT_FAILURE;

            // Creating the new file
            feedback = create_file(new_name, new_name, FALSE, &new_file);
            if (feedback)
                return EXIT_FAILURE;
            

            // Operation
            char last_operation = 0;

            // Remove Singleline Comments
            for (int i = 0; i < AMOUNTCOMMAND; i++) {
                if (commands[0] == 0 || commands[i] == 's') {
                    feedback = remove_singleline_comments(&temp_file, &new_file);
                    last_operation = commands[i];
                    if (feedback)
                        return EXIT_FAILURE;
                    break;
                }
            }
            
            // Save changes to TEMP
            for (int i = 0; i < AMOUNTCOMMAND; i++) {
                if (commands[0] == 0 || (commands[i] == 'm' && last_operation != 0)) {
                    feedback = save_changes(&temp_file, &new_file);
                    last_operation = commands[i];
                    if (feedback) {
                        printf("%s >> Não foi possivel salvar as mudanças para o arquivo temporário.\n", ERRORMESSAGE);
                        return EXIT_FAILURE;
                    }
                    break;
                }
            }
            
            // Remove Multipleline Comments
            for (int i = 0; i < AMOUNTCOMMAND; i++) {
                if (commands[0] == 0 || commands[i] == 'm') {
                    feedback = remove_multiline_comments(&temp_file, &new_file);
                    last_operation = commands[i];
                    if (feedback)
                        return EXIT_FAILURE;
                    break;
                }
            }
            
            printf("%s >> Uma cópia do arquivo \'%s\' foi gerada com sucesso!\n", SUCCESSMESSAGE, original_file.path);
            
            // Restartar loop
            free(new_file.path);
            close_ex23_body(&new_file);
            change_file_mode(&temp_file, "w"); 
        }
    }

    // Excluir arquivo .temp.c antes de finalizar o programa
    close_ex23_body(&temp_file);
    delete_file(&temp_file);
    
    return EXIT_SUCCESS;
}