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

void switchSubject(String subject, int *isInSubject) {
    String *homePath;
    homePath = make_empty_String();

    getcwd(homePath->str, MAX_LEN);
    int strLen = strlen(homePath->str);
    char* something = (char*) malloc(sizeof(char) * 100);
    if(*isInSubject) {
        int lastForward = -1;
        for (int i = 0 ; i < strLen; i++) {
            if (homePath->str[i] == '/') lastForward = i;
        }
        int counter = 0;
        for (int i = lastForward + 1; i < strLen; i++) {
            subj->str[counter] = homePath->str[i];
            counter++;
        }
        subj->str[counter] = '\0';
        exitCurrentDirectory();
    }
    // Finding the current subject name
    // going back to the prev dir i.e where all the
    // subj folders are present

    int flag = folderExists(subject); // checking if the subject exists

    if (!flag)
    {
        printf("The Subject %s doesn't exist\n", subject.str);
        if(*isInSubject == 1) chdir(subj->str);
    }
    else
    {
        chdir(subject.str); // changes the cwd to the subject entered by the user
        *isInSubject = 1;
        getcwd(homePath->str, MAX_LEN); // here it gets the path of the cwd i.e
                                        // after we switch to the subject
    }

    return;
}