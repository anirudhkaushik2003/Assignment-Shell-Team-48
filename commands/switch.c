#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "switch.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include "../utils/sysinfo.h"
#include "../globals.h"

#define MAX_LEN 2000
void exitCurrentDirectory() {
    String* dots = make_String("..");
    chdir(dots->str);
}

void switchSubject(String subject) {
    String *homePath;
    homePath = make_empty_String();

    getcwd(homePath->str, MAX_LEN);
    int strLen = strlen(homePath->str);
    String* currentSubject = getCurrentSubject();
    if(isInSubject) {
        exitCurrentDirectory();
    }
    // going back to the prev dir i.e where all the
    // subj folders are present

    int flag = folderExists(subject); // checking if the subject exists

    if (!flag)
    {
        printf("\n\tSubject \"%s\" doesn't exist\n\n", subject.str);
        if(isInSubject == 1) chdir(currentSubject->str);
    }
    else
    {
        chdir(subject.str); // changes the cwd to the subject entered by the user
        isInSubject = 1;
        getcwd(homePath->str, MAX_LEN); // here it gets the path of the cwd i.e
                                        // after we switch to the subject
    }

    return;
}

void commandSwitch(token_mat args_mat) {
    if (args_mat.num_args != 1) {
        printf("\n\tInvalid usage of the switch command\n\n");
        printf("\tswitch command syntax: switch <subject> \n\n");
    }
    else {
        String *subjectName = make_String(args_mat.args[1]);
        switchSubject(*subjectName);
    }
}
