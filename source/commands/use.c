#include "use.h"
#include "../utils/files.h"

void updateUseGlobal()
{
    UseCond = 1;
}

void useAssignment(String assignmentName) {
    if (!folderExists(assignmentName)) {
        String* error = make_empty_String();
        sprintf(error->str, "\n\tERROR: Assignment \"%s\" doesn't exist\n\n", assignmentName.str);
        printError(*error);
        return;
    }

    // Assigns the assignment name to the global variable
    UseAssignmentName = make_String(assignmentName.str);
    UseAssignmentName->length = strlen(UseAssignmentName->str);

    updateUseGlobal(); //updates global variable to be able to use the USE function
}

void commandUse(token_mat args_mat)
{
    if (args_mat.num_args != 1) {
        String* error = make_String("\n\tERROR: Invalid usage of the use command\n\n\tuse command syntax: use <assignment> \n\n");
        printError(*error);
    }
    else if (!isInSubject) {
        String* error = make_String("\n\tERROR: You are not in a Subject yet\n\n");
        printError(*error);
    }
    else {
        String* assignmentName = make_String(args_mat.args[1]);
        useAssignment(*assignmentName);
    }
}