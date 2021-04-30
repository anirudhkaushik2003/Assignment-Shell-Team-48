#include "switch.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LEN 2000

void switchSubject(string subject,int inSubject) {

  string homePath;
  homePath = make_empty_string();

  getcwd(homePath->str, MAX_LEN);

  int strLen = strlen(homePath->str);
  string subj;
  subj = make_empty_string();
  int count = 0;
  for (int i = strLen; i > 0; i--) {
    if (homePath->str[i] != '/')
      subj->str[count++] = homePath->str[i];
    else
      break;
  }
  subj->[count] = '\0';
  subj->size = strLen(subj->str);
  char temp;
  int len = subj->size - 1;
  int k = len;

  for (int i = 0; i < len; i++) {
    temp = subj->str[k];
    subj->str[k] = subj->str[i];
    subj->str[i] = temp;
    k--;

    if (k == (len / 2)) {
      break;
    }
  }// reverses the subj

  if (strcmp(subj->str, subject->str) == 0) {
    printf("%s ", homePath->str);
    return; // already in the specified subj
  } else if (inSubject) {
      chdir(".."); // going back to the prev dir i.e where all the
  }                // subj folders are present

  int flag = folderExists(subject); // checking if the subject exists

  if (!flag) {
    printf("The Subject %s doesn't exist\n", subject->str);
    chdir(subj->str);
    printf("%s ", getcwd(homePath->str, MAX_LEN));
    return;
  } else {
    chdir(subject->str); // changes the cwd to the subject entered by the user

    getcwd(homePath->str, MAX_LEN); // here it gets the path of the cwd i.e
                                    // after we switch to the subject

    printf("%s ", homePath->str);
  }

  return;
}