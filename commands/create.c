#include "create.h"
#include "../utils/files.h"
#include "../utils/string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void createassignment(String *serverpath, String *assignment) {
  String *folder;

  folder = attach_String(serverpath->str, "/");
  folder = attach_String(folder->str, assignment->str);

  if (!folderExists(*folder))
    printf(
        "\n\tERROR!,No such assignment exists in server\n"); // checks whether
                                                             // assignment exists
                                                             // on server/
  else if (folderExists(*assignment))
    printf("\n\tThis assignment was already created\n"); // checks whether
                                                         // assignment was
                                                         // already created//
  else {
    createFolder(*assignment); // creates folder for assignment//

    String *dist = attach_String(folder->str, "/dist");

    String *command = make_empty_String();

    sprintf(command->str, "find %s/ -name '*.pdf' -exec cp -pr '{}' '%s/' ';'",
            folder->str,
            assignment->str); // finds all pdf files present in server and
                              // copies them to assignment
    system(command->str);
    sprintf(
        command->str, "cp -r  %s %s> /dev/null", dist->str,
        assignment->str); // copies dist folder from server into assignment//
    system(command->str);
  }
}

void commandCreate(token_mat args_mat) {

  if (args_mat.num_args != 1) {
    printf("\n\tInvalid usage of the create command\n\n");
    printf("\tcreate command syntax: create <assignment> \n\n");
  } else if (!isInSubject) {
    printf("\n\tError: You are not in a Subject yet\n\n");
  } else {
    String *assignmentName = make_String(args_mat.args[1]);
    String *currsubj = getCurrentSubject();
    String *serverpath = make_String("../../Server/");
    serverpath = attach_String(serverpath->str, currsubj->str);
    createassignment(serverpath, assignmentName);
  }
}
