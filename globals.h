#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "processor/input.h"

#define MAX_NUM_OF_TOKENS 20
#define MAX_TOKEN_LENGTH 100

typedef struct Pathways Pathways;

struct Pathways
{
    char *str;
    int length;
};

String *subj;
int start_point;
int isInSubject;

String home_path;
String server_path;
String prev_path;

#endif
