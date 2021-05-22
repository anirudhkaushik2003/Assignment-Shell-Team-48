#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "../utils/string.h"
#include "submit.h"
#include "../utils/files.h"

// supporting function which creates zip for assignment folder
int createAssignmentZip(String path)
{
    return createZip(path, path);
}

/* this function is called upon when we are in a subject directory and 
the submit command was used properly 
without any wrong syntax
*/
void userCommandSubmit(String folder)
{
    String *zip_name = make_empty_String();

    // Deleting zip if it exists
    sprintf(zip_name->str, "%s.zip", folder.str);
    deleteFile(*zip_name);

    // Creates zip
    int successful = createAssignmentZip(folder);

    if (successful) {
        String* success = make_empty_String();
        sprintf(success->str, "\n\t%s created successfully\n\n", zip_name->str);
        printSuccess(*success);
    }
    else
    {
        String* error = make_empty_String();
        sprintf(error->str, "\n\tERROR: Assignment \"%s\" doesn't exist\n\n", folder.str);
        printError(*error);
    }

    IFsubmission_folder(folder, zip_name);

    if (successful)
    {
        if (copy_to_server(zip_name, folder))
        {
            String* success = make_empty_String();
            sprintf(success->str, "\n\t%s successfully submitted to server\n\n", zip_name->str);
            printSuccess(*success);
        }
        else
        {
            String* error = make_empty_String();
            sprintf(error->str, "\n\tERROR: %s wasn't copied due to duplicate\n\n", zip_name->str);
            printError(*error);
        }
    }
}

/* this is the function that is being called by the tokenizer and input is 
provided to it and it checks edge cases and then only send the input
further to main submit function which does its operation as defined
*/
void commandSubmit(token_mat args_mat)
{
    if (args_mat.num_args != 1)
    {
        String* error = make_String("\n\tERROR: Invalid usage of the submit command\n\n\tsubmit command syntax: setup <assignment>\n\n");
        printError(*error);
    }
    else if (!isInSubject)
    {
        String* error = make_String("\n\tERROR: You are not in a Subject yet\n\n");
        printError(*error);
    }
    else
    {
        String *fileName = make_String(args_mat.args[1]);
        userCommandSubmit(*fileName);
    }
}
