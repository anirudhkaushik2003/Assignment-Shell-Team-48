#include "tokenizer.h"
#include "../commands/execvp.h"
#include "../commands/switch.h"
#include "../commands/compare.h"
#include "../commands/test.h"
#include "../commands/setup.h"
#include "../commands/submit.h"
#include "../commands/create.h"
#include "../commands/use.h"
#include "../commands/update.h"
#include "../commands/tree.h"
void tokenize_input(String Input)
{
    token_mat args_mat;
    args_mat = make_args_mat();
    char *token;
    token = strtok(Input.str, " "); //tokenize the input string
    int i = 0;

    if (strcmp(token, "quit") == 0) //exit
    {
        char pet[] = "            ,.  ,.\n            ||  ||\n           ,''--''.\n          : (^)(^) :\n         ,'  -__-  `.\n         :          :\n         :          :\n   -ctr- `._m____m_,' \n";
        printf(ORANGE);
        printf("%s", pet);
        printf(RESET);
        printf(GREEN);
        printf("Exiting...\n");
        printf(RESET);
        sleep(1);
        exit(0);
    }
    if (strcmp(token, "list") == 0) //rename list to ls
    {
        strcpy(token, "ls");
    }

    while (token != NULL) //store the tokenized string in a token matrix
    {
        args_mat.args[i] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
        strcpy(args_mat.args[i], token);
        token = strtok(NULL, " ");
        i++;
    }
    args_mat.num_args = i - 1; //number of arguments to a command
    args_mat.args[i] = token;
    execute(args_mat); //send it to the required command
}

void execute(token_mat args_mat)
{
    if (strcmp(args_mat.args[0], "switch") == 0)
    {
        commandSwitch(args_mat);
    }
    else if (strcmp(args_mat.args[0], "compare") == 0)
    {
        if (args_mat.num_args == 1 && UseCond == 1)
        {
            args_mat.args[2] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
            strcpy(args_mat.args[2], args_mat.args[1]);
            strcpy(args_mat.args[1], UseAssignmentName->str);
            args_mat.args[3] = NULL;
            args_mat.num_args++;
        }

        commandCompare(args_mat);
    }
    else if (strcmp(args_mat.args[0], "test") == 0)
    {
        if (args_mat.num_args == 0 && UseCond == 1)
        {
            args_mat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
            strcpy(args_mat.args[1], UseAssignmentName->str);
            args_mat.args[2] = NULL;
            args_mat.num_args++;
        }

        commandTest(args_mat);
    }
    else if (strcmp(args_mat.args[0], "setup") == 0)
    {
        if (args_mat.num_args == 0 && UseCond == 1)
        {
            args_mat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
            strcpy(args_mat.args[1], UseAssignmentName->str);
            args_mat.args[2] = NULL;
            args_mat.num_args++;
        }

        commandSetup(args_mat);
    }
    else if (strcmp(args_mat.args[0], "submit") == 0)
    {
        if (args_mat.num_args == 0 && UseCond == 1)
        {
            args_mat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
            strcpy(args_mat.args[1], UseAssignmentName->str);
            args_mat.args[2] = NULL;
            args_mat.num_args++;
        }

        commandSubmit(args_mat);
    }
    else if (strcmp(args_mat.args[0], "create") == 0)
    {
        if (args_mat.num_args == 0 && UseCond == 1)
        {
            args_mat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
            strcpy(args_mat.args[1], UseAssignmentName->str);
            args_mat.args[2] = NULL;
            args_mat.num_args++;
            //This was intentional
        }

        commandCreate(args_mat);
    }
    else if (strcmp(args_mat.args[0], "update") == 0)
    {
        if (args_mat.num_args == 0 && UseCond == 1)
        {
            args_mat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
            strcpy(args_mat.args[1], UseAssignmentName->str);
            args_mat.args[2] = NULL;
            args_mat.num_args++;
        }
        commandUpdate(args_mat);
    }
    else if (strcmp(args_mat.args[0], "tree") == 0)
    {
        if (args_mat.num_args == 0 && UseCond == 1)
        {
            args_mat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
            strcpy(args_mat.args[1], UseAssignmentName->str);
            args_mat.args[2] = NULL;
            args_mat.num_args++;
        }
        commandTree(args_mat);
    }
    else if (strcmp(args_mat.args[0], "use") == 0)
    {
        commandUse(args_mat);
    }
    else if (strcmp(args_mat.args[0], "ls") == 0)
    {
        exec(args_mat);
    }
    else
    {
        String *error = make_empty_String();
        sprintf(error->str, "\n\tERROR: Invalid command \"%s\"\n\n", args_mat.args[0]);
        printError(*error);
    }
}