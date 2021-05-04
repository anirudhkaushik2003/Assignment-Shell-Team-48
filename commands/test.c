#include "test.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void test(String folder) {
  String *file = make_empty_String();

  file = attach_String(folder.str, "/dist/submitter.py");

  int flag1 = folderExists(folder) && fileExists(*file);

  if (!flag1) {

    if (!folderExists(folder)) // checks whether given assignment exists//
      printf("Assignment %s doesn't exist\n", folder.str);
    if (!fileExists(*file)) // checks whether submitter.py exists in assignment//
      printf("Current assignment %s cannot be tested as it does not contain "
             "submitter.py file",
             folder.str);

  } else {
    int flag2, flag3, i = 1;

    String *filename = make_empty_String();
    String *logfile;

    String *Logs = make_String("Logs");
    flag2 = folderExists(*Logs);

    if (flag2 == 0) {       // checks whether Logs folder exists
      system("mkdir Logs"); // if not creates a new folder Logs
    }

    while (1) {
      sprintf(filename->str, "Logs/%d.log", i);

      logfile = make_String(filename->str);
      flag3 = fileExists(*logfile); // checks whether file i.log already exists//

      if (flag3 == 0)
        break;

      i++;
    }

    printf("%s will be created\n", logfile->str);
    String *runcommand = make_empty_String();
    sprintf(runcommand->str, "python3 %s/dist/submitter.py > Logs/%d.log",
            folder.str,
            i); // runs submitter.py and store logs in Logs/i.log file //

    system(runcommand->str);
  }
}
