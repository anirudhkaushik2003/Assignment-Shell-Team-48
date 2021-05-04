#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../globals.h"

typedef struct arg_mat token_mat;

struct arg_mat
{
    char **args;
    int num_args;

};

token_mat make_args_mat();
#endif