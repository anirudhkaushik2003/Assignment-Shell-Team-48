#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../utils/files.h"
#include "../utils/string.h"

int verifyIntegrity(string folder, string file) {
	string command = make_empty_string();
	// Create a temporary zip file of the current state of the folder 
	string zipFile = make_string("temporaryMD5Check");
	createZip(folder, zipFile);

	// Calculate the md5sum of the zip we are comparing and the zip we just created
	// And output it to a file
	sprintf(command->str, "md5sum temporaryMD5Check.zip %s > hashCheck.md5", file->str);
	system(command->str);

	// Delete the temporary zip file we created since we only needed it to compare md5sum;
	string zipFileWithExtension = make_string("temporaryMD5Check");
	deleteFile(zipFileWithExtension);
	
	// Compare the two hashvalues
	
	string hashOfTemporaryFile = make_empty_string(), 
            nameOfTemporaryFile = make_empty_string(); 

	string hashOfZipFile = make_empty_string(), 
            nameOfZipFile = make_empty_string();

	FILE* fp = fopen("hashCheck.md5", "r");

	fscanf(fp, "%s %s", hashOfTemporaryFile->str, nameOfTemporaryFile->str);
	fscanf(fp, "%s %s", hashOfZipFile->str, nameOfZipFile->str);
	
	string hashFile = make_string("hashCheck.md5");
	deleteFile(hashFile);

	// Returns true if the files are equal, false if otherwise

	return compare_string(hashOfTemporaryFile->str,hashOfZipFile->str) == 0; 
}


void userCommandCompare(string folder, string file) {

	// Checking if the folder and file exists before verifying integrity 
	int flag = folderExists(folder) && fileExists(file);

	if (!flag) {

		if (!folderExists(folder))
			printf("Assignment %s doesn't exist\n", folder->str);
		if (!fileExists(file)) 
			printf("File %s doesn't exist\n", file->str);

	}
	else {

		if(verifyIntegrity(folder,file))
			printf("The integrity is maintained\n");
		else 
			printf("The integrity is not maintained\n");

	}
}
