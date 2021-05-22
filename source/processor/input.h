#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define LENGTH 1000
typedef struct String String;
struct String
{
    char *str;
    int length;
};

#endif