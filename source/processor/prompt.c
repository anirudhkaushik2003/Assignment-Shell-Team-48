#include "prompt.h"
#include "../globals.h"
#include "../utils/files.h"
void Initialize() //initialize the home_path and prev_path
{
    home_path.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    getcwd(home_path.str, MAX_TOKEN_LENGTH);
    home_path.length = strlen(home_path.str);

    prev_path.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    getcwd(prev_path.str, MAX_TOKEN_LENGTH);
    prev_path.length = strlen(prev_path.str);
}

void prompt_print() //print the username and subject to give terminal feel
{
    if (UseCond)
    {
        printf(BLUE);
        printf("<%s:", get_username().str);
        printf(RESET);
        printf(ORANGE);
        printf("%s", getCurrentSubject()->str);
        printf(RESET);
        printf(BLUE);
        printf("/");
        printf(RESET);
        printf(LIGHT_PURPLE);
        printf("<%s>", UseAssignmentName->str);
        printf(RESET);
        printf(BLUE);
        printf("$ ");
        printf(RESET);
    }
    else
    {
        printf(BLUE);
        printf("<%s:", get_username().str);
        printf(RESET);
        printf(ORANGE);
        printf("%s", getCurrentSubject()->str);
        printf(RESET);
        printf(BLUE);
        printf("/$ ");
        printf(RESET);
    }

    fflush(stdout);
}
