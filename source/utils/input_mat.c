#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "input_mat.h"

token_mat make_args_mat() //initializes the token matrix to store user command name and arguments
{
    token_mat args_mat; 
    
    args_mat.args = malloc(sizeof(char *)*MAX_NUM_OF_TOKENS);
    for (int i = 0; i < MAX_NUM_OF_TOKENS; i++)
    {
        args_mat.args[i] = malloc(sizeof(char)*MAX_TOKEN_LENGTH);
    }
    return args_mat;

}