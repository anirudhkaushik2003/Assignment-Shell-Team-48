#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "compare.h"
#include "../utils/files.h"
#include "../utils/string.h"

/* Creates a list of hashes of each file recursively in the assignment specified and stores it in a
 * file name specified by hashName
 * The files are in sorted order as it makes it easier to compare the hashes later
 */
void folderHash(String assignmentName, String hashName) {
    String* command = make_empty_String();
    sprintf(command->str,"find %s -type f -print0 | sort -z | xargs -r0 md5sum > %s", assignmentName.str, hashName.str);
    system(command->str);
}

/* Unzips a zip file into a temporary folder, generates a list of it's hashes and
 * then deletes the temporary folder that was created
 */
void zipHash(String fileName, String hashName) {
    unzipToDirectory(fileName, *make_String("TemporaryMD5/"));
    folderHash(*make_String("TemporaryMD5/"), hashName);
    deleteFolder(*make_String("TemporaryMD5"));
}

/* Goes line by line through both the files at the same time, first compares if the path names
 * are equal.
 *
 * 1. If they are equal and the hash values are equal, the integrity of that file is maintained.
 * 2. If they are equal but the hash values aren't, that file has been modified.
 * 3. In case the file in the directory is lexicographically greater than the current file in the zip
 * file, then we know that a file is missing in the directory
 * 4. If the file in the zip is lexicographically greater, we know the zip files is missing some file.
 *
 * In case only case 1 occurs, that means the integrity is maintained
 */
void compareHash(String file1, String file2) {
    int assignmentFileLines = countLines(file1);
    int zipFileLines = countLines(file2);

    FILE* assignmentFileHash = fopen(file1.str, "r");
    FILE* zipFileHash = fopen(file2.str, "r");

    String* hash1 = make_empty_String(), *hash2 = make_empty_String();
    String* path1 = make_empty_String(), *path2 = make_empty_String();

    int flag = 1;
    int prefixLength = strlen("TemporaryMD5/"); // Need to skip the prefix of the unzipped folder

    printf("\n"); // Printing a new line so errors can be more visibly distinct

    // Taking initial input of file
    fscanf(assignmentFileHash, "%s %s", hash1->str, path1->str);
    fscanf(zipFileHash, "%s %s", hash2->str, path2->str);

    int indexAssignment = 0, indexZip = 0;

    while (indexAssignment < assignmentFileLines && indexZip < zipFileLines) {

        int comparePaths = strcmp(path1->str, &(path2->str[prefixLength]));

        // If the two files have the same path and name, compare their hash values
        if (comparePaths == 0) {

            if (strcmp(hash1->str, hash2->str) != 0) {
                String* error = make_empty_String();
                sprintf(error->str, "\t%s has been modified\n", path1->str);
                printError(*error);
                flag = 0;
            }

            // Increment both lines as they are equal paths
            fscanf(assignmentFileHash, "%s %s", hash1->str, path1->str);
            fscanf(zipFileHash, "%s %s", hash2->str, path2->str);

            indexAssignment++;
            indexZip++;
        }
        else if (comparePaths > 0) {  // Implies a file has been deleted from the directory
            String* error = make_empty_String();
            sprintf(error->str,"\t%s is in the zip file but not in the directory\n", &(path2->str[prefixLength]));
            printError(*error);
            flag = 0; // Integrity is not maintained so we change the flag

            // Increment the lines in the zip file as it's lexicographically behind
            fscanf(zipFileHash, "%s %s", hash2->str, path2->str);
            indexZip++;
        }
        else { // A new file was added into the directory
            String* error = make_empty_String();
            sprintf(error->str,"\t%s is in the directory but not in the zip file\n", path1->str);
            printError(*error);
            flag = 0; // Integrity is not maintained so we change the flag

            // Increment the lines in the directory as it's lexicographically behind
            fscanf(assignmentFileHash, "%s %s", hash1->str, path1->str);
            indexAssignment++;
        }
    }

    // Going over the leftover lines in the hash value checklist
    while (indexZip < zipFileLines) {
        String* error = make_empty_String();
        sprintf(error->str,"\t%s is in the zip file but not in the directory\n", &(path2->str[prefixLength]));
        printError(*error);

        flag = 0;

        fscanf(zipFileHash, "%s %s", hash2->str, path2->str);
        indexZip++;
    }

    while (indexAssignment < assignmentFileLines) {
        String* error = make_empty_String();
        sprintf(error->str,"\t%s is in the directory but not in the zip file\n", path1->str);
        printError(*error);

        flag = 0;

        fscanf(assignmentFileHash, "%s %s", hash1->str, path1->str);
        indexAssignment++;
    }

    if (flag) { // flag = 1 indicates there was no difference in the files
        String* success = make_String("\tThe integrity is maintained\n");
        printSuccess(*success);
    }

    printf("\n");
}

void verifyIntegrity(String folder, String file) {

    // Create hashes of the assignment and the zip
    folderHash(folder, *make_String("checkList.chk"));
    zipHash(file, *make_String("checkList2.chk"));

    // Compare the hash values and the files
    compareHash(*make_String("checkList.chk"), *make_String("checkList2.chk"));

    // Delete the temporary files created
    deleteFolder(*make_String("TemporaryMD5")); // Created in zipHash when we unzip
    deleteFile(*make_String("checkList.chk"));
    deleteFile(*make_String("checkList2.chk"));
}

void compareAssignment(String folder, String file) {

    // Checking if the folder and file exists before verifying integrity
    int flag = folderExists(folder) && fileExists(file);

    if (!flag) {
        if (!folderExists(folder)) {
            String* error = make_empty_String();
            sprintf(error->str, "\n\tERROR: Assignment \"%s\" doesn't exist\n", folder.str);
            printError(*error);
        }
        if (!fileExists(file)) {
            String* error = make_empty_String();
            sprintf(error->str,"\n\tERROR: File \"%s\" doesn't exist\n", file.str);
            printError(*error);
        }
        printf("\n");
    }
    else {
        // If they both exist then verify their integrity
        verifyIntegrity(folder, file);
    }
}

void commandCompare(token_mat args_mat) {
    if (args_mat.num_args != 2) {
        String* error = make_String("\n\tERROR: Invalid usage of the compare command\n\n\tcompare command syntax: compare <assignment> <zipfile> \n\n");
        printError(*error);
    }
    else if (!isInSubject) {
        String* error = make_String("\n\tERROR: You are not in a Subject yet\n\n");
        printError(*error);
    }
    else {
        String *folder = make_String(args_mat.args[1]);
        String *file = make_String(args_mat.args[2]);

        compareAssignment(*folder, *file);
    }
}
