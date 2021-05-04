#include "prompt.h"

void Initialize()

{
    home_path.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    getcwd(home_path.str, MAX_TOKEN_LENGTH);
    home_path.length = strlen(home_path.str);

    prev_path.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    getcwd(prev_path.str, MAX_TOKEN_LENGTH);
    prev_path.length = strlen(prev_path.str);
}

void prompt_print()
{
    printf("<%s@%s:%s$ ", get_username().str, get_machine_name().str, get_pwd().str);
    fflush(stdout);
}