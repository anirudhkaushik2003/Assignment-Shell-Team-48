#include "tokenizer.h"
#include "../commands/execvp.h"
#include "../commands/switch.h"

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
        //printf("%s\n", token);
        token = strtok(NULL, " ");
        i++;
    }
    //printf("i = %d\n",i);
    args_mat.num_args = i - 1;
    args_mat.args[i] = token;
    execute(args_mat);
}

void execute(token_mat args_mat)
{
    String *command;
    command = malloc(sizeof(String));
    command->str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    if (strcmp(args_mat.args[0], "switch") == 0)
    {
        strcpy(command->str, args_mat.args[1]);
        command->length = strlen(args_mat.args[1]) + 1;
        printf("foldername = %s\n",command->str);
        switchSubject(command, &insubject);
    }
    else
        exec(args_mat);
}