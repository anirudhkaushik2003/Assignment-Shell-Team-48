#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "compare.h"
#include "../utils/files.h"
#include "../utils/string.h"

int verifyIntegrity(String folder, String file) {
	String* command = make_empty_String();

	// Create a temporary zip file of the current state of the folder 
	String* zipFile = make_String("temporaryMD5Check");
	createZip(folder, *zipFile);

	// Calculate the md5sum of the zip we are comparing and the zip we just created
	// And output it to a file
	sprintf(command->str, "md5sum temporaryMD5Check.zip %s > hashCheck.md5", file.str);
	system(command->str);

	// Delete the temporary zip file we created since we only needed it to compare md5sum;
	String* zipFileWithExtension = make_String("temporaryMD5Check");
	deleteFile(*zipFileWithExtension);
	
	// Compare the two hashvalues
	
	String *hashOfTemporaryFile = make_empty_String(), 
            *nameOfTemporaryFile = make_empty_String(); 

	String *hashOfZipFile = make_empty_String(), 
            *nameOfZipFile = make_empty_String();

	FILE* fp = fopen("hashCheck.md5", "r");

	fscanf(fp, "%s %s", hashOfTemporaryFile->str, nameOfTemporaryFile->str);
	fscanf(fp, "%s %s", hashOfZipFile->str, nameOfZipFile->str);
	
	String *hashFile = make_String("hashCheck.md5");
	deleteFile(*hashFile);

	// Returns true if the files are equal, false if otherwise

	return compare_String(*hashOfTemporaryFile,*hashOfZipFile) == 0; 
}


void compareAssignment(String folder, String file) {

	// Checking if the folder and file exists before verifying integrity 
	int flag = folderExists(folder) && fileExists(file);

	if (!flag) {

		if (!folderExists(folder))
			printf("\n\tAssignment \"%s\" doesn't exist\n", folder.str);
		if (!fileExists(file)) 
			printf("\n\tFile \"%s\" doesn't exist\n", file.str);
        printf("\n");
	}
	else {

		if(verifyIntegrity(folder,file))
			printf("\n\tThe integrity is maintainedn\n\n");
		else 
			printf("\n\tThe integrity is not maintained\n\n");

	}
}
void commandCompare(token_mat args_mat) {
    if (args_mat.num_args != 2) {
        printf("\n\tInvalid usage of the compare command\n\n");
        printf("\tcompare command syntax: compare <assignment> <zipfile> \n\n");
    }
    else if (!isInSubject) {
        printf("\n\tError: You are not in a Subject yet\n\n");
    }
    else {
        String *folder = make_String(args_mat.args[1]);
        String *file = make_String(args_mat.args[2]);
        compareAssignment(*folder, *file);
    }
}
