#ifndef __PROMPT_H__
#define __PROMPT_H__

#include "../globals.h"
#include "input.h"
#include "../utils/sysinfo.h"
#include "../globals.h"
#include <unistd.h>

String home_path;
String server_path;
String prev_path;

void Initialize();
void prompt_print();

int exit_code;

#endif