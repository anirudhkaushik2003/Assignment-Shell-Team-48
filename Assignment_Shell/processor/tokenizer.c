#include "tokenizer.h"


void tokenize_input(String Input)
{
    token_mat args_mat;
    args_mat = make_args_mat();
    char *token;
    token = strtok(Input.str, " ");
    int i = 0;
    if (strcmp(token, "create") == 0)
    {
        strcpy(token, "mkdir");
    }
    if (strcmp(token, "delete") == 0)
    {
        strcpy(token, "rmdir");
    }
    if (strcmp(token, "quit") == 0)
    {
        exit(0);
    }

    while (token != NULL)
    {

        args_mat.args[i] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
        strcpy(args_mat.args[i], token);
        printf("%s\n", token);
        token = strtok(NULL, " ");
        i++;
    }
    //printf("i = %d\n",i);
    args_mat.num_args = i - 1;
    args_mat.args[i] = token;
}