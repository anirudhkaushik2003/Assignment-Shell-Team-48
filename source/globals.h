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

extern String *subj;
extern int start_point;
extern int isInSubject;

extern String home_path;
extern String *server_path;
extern String prev_path;

extern int Server_file_count;
extern String *Subject_array; //stores all the subject names

extern int UseCond;
extern String *UseAssignmentName; //stores the Assignment name


#define BOLD "\033[1m"
#define NO_BOLD "\033[22m"
#define RED "\033[38;5;1m"
#define GREEN "\033[38;5;121m"
#define ORANGE "\033[38;5;209m"
#define PURPLE "\033[38;5;205m"
#define LIGHT_PINK "\033[38;5;225m"
#define LIGHT_PURPLE "\033[38;5;213m"
#define YELLOW "\033[38;5;223m"
#define RESET "\033[0m"
#define BLUE "\033[0;34m"

#endif
