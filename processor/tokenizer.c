#include "tokenizer.h"
#include "../commands/execvp.h"
#include "../commands/switch.h"
#include "../commands/compare.h"
#include "../commands/test.h"
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
        token = strtok(NULL, " ");
        i++;
    }
    args_mat.num_args = i - 1;
    args_mat.args[i] = token;
    execute(args_mat);
}

void execute(token_mat args_mat)
{
    if (strcmp(args_mat.args[0], "switch") == 0) {
        commandSwitch(args_mat);
    }
    else if(strcmp(args_mat.args[0], "compare") == 0) {
        commandCompare(args_mat);
    }
    else if(strcmp(args_mat.args[0], "test") == 0) {
        commandTest(args_mat);
    }
    else
        exec(args_mat);
}