#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../utils/input_mat.h"
#include "input.h"

void tokenize_input(String Input);
void execute(token_mat args_mat);

#endif

