#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "test.h"
#include "../utils/files.h"
#include "../utils/string.h"

void test(String folder)
{
  String *file;

  file = attach_String(folder.str, "/dist/submitter.py");

  int flag1 = folderExists(folder) && fileExists(*file);

  if (!flag1)
  {

    if (!folderExists(folder)) { // checks whether given assignment exists//
        String* error = make_empty_String();
        sprintf(error->str, "\n\tERROR: Assignment \"%s\" doesn't exist\n", folder.str);
        printError(*error);
    }
    else if (!fileExists(*file)) { // checks whether submitter.py exists in assignment//
        String* error = make_empty_String();
        sprintf(error->str, "\n\tERROR: Assignment \"%s\" cannot be tested as it does not contain "
               "submitter.py file\n",
               folder.str);
        printError(*error);
    }

    printf("\n");
  }
  else
  {
    int i = 1;

    String *filename = make_empty_String();
    String *logfile;

    createFolder(*make_String("Logs")); // Creates folder Logs if it doesn't exist

    while (1)
    {
      sprintf(filename->str, "Logs/%d.txt", i);

      logfile = make_String(filename->str);

      // if such a file doesn't exist we can use it
      if (!fileExists(*logfile))
        break;

      i++;
    }

    printf("\n\t%s will be created\n\n", logfile->str);
    String *runcommand = make_empty_String();
    sprintf(runcommand->str, "python3 %s/dist/submitter.py > Logs/%d.txt",
            folder.str,
            i); // runs submitter.py and store logs in Logs/i.log file //

    system(runcommand->str);
  }
}

void commandTest(token_mat args_mat)
{
  if (args_mat.num_args != 1)
  {
      String* error = make_String("\n\tERROR: Invalid usage of the test command\n\n\ttest command syntax: test <assignment>\n\n");
      printError(*error);
  }
  else if (!isInSubject)
  {
      String* error = make_String("\n\tERROR: You are not in a Subject yet\n\n");
      printError(*error);
  }
  else
  {
    String *assignmentName = make_String(args_mat.args[1]);
    test(*assignmentName);
  }
}
