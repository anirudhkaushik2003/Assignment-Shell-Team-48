#ifndef __SYS_INFO_H__
#define __SYS_INFO_H__

#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "string.h"
#include "../globals.h"
#include "../processor/input.h"

String get_username();
String get_machine_name();
String get_pwd();
void out_pwd();

#endif