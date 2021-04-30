#include "switch.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../utils/sysinfo.h"
#include "../globals.h"

#define MAX_LEN 2000

void switchSubject(String *subject, int *insubject)
{

    String *homePath;
    homePath = make_empty_String();

    getcwd(homePath->str, MAX_LEN);

    int strLen = strlen(homePath->str);

    int count = 0;
    for (int i = strLen; i > 0; i--)
    {
        if (homePath->str[i] != '/')
            subj->str[count++] = homePath->str[i];
        else
            break;
    }
    subj->str[count] = '\0';
    subj->length = strlen(subj->str);

    char temp;
    int len = subj->length - 1;
    int k = len;

    for (int i = 0; i < len; i++)
    {
        temp = subj->str[k];
        subj->str[k] = subj->str[i];
        subj->str[i] = temp;
        k--;

        if (k == (len / 2))
        {
            break;
        }
    } // reverses the subj

    strcpy(subj->str, subject->str);

    if (insubject == 0)
    {
        char *inSubject;
        insubject = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
        strcpy(insubject, "..");
        strcat(insubject, subject->str);
        chdir(insubject);
    }
    // going back to the prev dir i.e where all the
    // subj folders are present

    int flag = folderExists(subject); // checking if the subject exists

    if (!flag)
    {
        printf("The Subject %s doesn't exist\n", subject->str);
        chdir(subj->str);
        //printf("%s ", getcwd(homePath->str, MAX_LEN));
        return;
    }
    else
    {
        chdir(subject->str); // changes the cwd to the subject entered by the user

        getcwd(homePath->str, MAX_LEN); // here it gets the path of the cwd i.e
                                        // after we switch to the subject

        //printf("%s ", homePath->str);
    }

    return;
}