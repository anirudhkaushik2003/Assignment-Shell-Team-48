#include "tree.h"
/* Dfs function that recursively prints the files and directories
 * of a given parent directory, with the indents showing the depth of the folder/file
 */
void dfsFiles(String path, int tabs, FILE* fp) {

    // Directory entry
    struct dirent *de;
    DIR *dr = opendir(path.str);

    if (dr == NULL) return;

    // Iterating through all directories of this directory
    while ((de = readdir(dr)) != NULL){

        // readdir gives ".", ".." as directories as well which we don't want, so we skip
        if(strcmp(".", de->d_name) == 0 ||
           strcmp("..", de->d_name) == 0) continue;

        // Print the number of indentations required
        for (int i = 0; i < tabs; i++) {
            fprintf(fp,"\t");
        }
        fprintf(fp,"%s", de->d_name);

        // Creating a path to the current file we're on to check if it's a directory or not
        String* a = make_String(path.str);
        strcat(a->str, "/");
        strcat(a->str, de->d_name);

        // If it's a directory, indicate by putting a forward slash and performing a dfs call
        if (folderExists(*a)) {
            fprintf(fp,"/\n");
            dfsFiles(*a, tabs + 1,fp); // Calls one level deeper, so an extra indentation
        }
        else fprintf(fp,"\n");
    }

    closedir(dr);
}

void printTree(String assignmentName) {

    // Don't print the tree if the assignment doesn't exist
    if (!folderExists(assignmentName)) {
        String* error = make_empty_String();
        sprintf(error->str, "\n\tERROR: Assignment \"%s\" doesn't exist\n\n", assignmentName.str);
        printError(*error);
    }
    else { // If the assignment exists enter the assignment and recursively print all the files
        String* path = make_String("./");
        path = attach_String(path->str, assignmentName.str);
        String* fileStructure = make_String(path->str);
        fileStructure = attach_String(fileStructure->str, "/fileStructure.txt");
        FILE* fp = fopen(fileStructure->str, "w");

        //Print the assignment name as the parent directory
        fprintf(fp,"%s/\n", assignmentName.str);

        //Recursively call this function to list all directories and files
        dfsFiles(*path, 1, fp);
        String* success = make_String("\n\tFile structure stored in fileStructure.txt\n\n");
        printSuccess(*success);
        fclose(fp);
    }
}

void commandTree(token_mat args_mat) {

    if (args_mat.num_args != 1) {
        String* error = make_String("\n\tERROR: Invalid usage of the tree command\n\n\ttree command syntax: tree <assignment>\n\n");
        printError(*error);
    }
    else if(!isInSubject) {
        String* error = make_String("\n\tERROR: You are not in a Subject yet\n\n");
        printError(*error);
    }
    else {
        String* assignmentName = make_String(args_mat.args[1]);
        printTree(*assignmentName);
    }

}
