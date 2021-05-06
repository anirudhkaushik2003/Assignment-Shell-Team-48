#include "../utils/files.h"
#include "../utils/string.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifndef _CREATE_H__
#define _CREATE_H__

void createassignment(String *serverpath, String *assignment);
void commandCreate(token_mat args_mat);
#endif
