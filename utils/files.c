#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>
#include "files.h"
#include "string.h"
int folderExists(string path) {
	struct stat sb;
	return stat(path->str, &sb) == 0 && S_ISDIR(sb.st_mode);
}

int fileExists(string path) {
	struct stat sb;
	return stat(path->str, &sb) == 0 && S_ISREG(sb.st_mode);
}

int deleteFile(string path) {
	if (!fileExists(path)) {
		return 0;
	}
	string command = make_empty_string();
	sprintf(command->str, "rm %s > /dev/null", path->str);
	system(command->str);
	return 1;
}

int deleteFolder(string path) {
	if (!folderExists(path)) {
		return 0;
	}
	string command = make_empty_string();
	sprintf(command->str, "rm -r %s > /dev/null", path->str);
	system(command->str);
	return 1;
}

int createZip(string path, string zipName) {
	if (!folderExists(path)) {
		return 0;	
	}	
	string command = make_empty_string();
	sprintf(command->str, "zip -r %s.zip %s > /dev/null", zipName->str, path->str);
	system(command->str);
	return 1;
}

int createFolder(string folder) {
	if (folderExists(folder)) {
		return 0;
	}

	string command = make_empty_string();
	sprintf(command->str, "mkdir %s > /dev/null", folder->str);
	system(command->str);
	return 1;
}
int validFileName(string name){
	string fileRegex = make_string("[^-_.A-Za-z0-9]");
	// string fileRegex = make_string("^(\\w+\\.?)*\\w+$ ");
	regex_t regex;
	int value = regcomp(&regex, fileRegex->str, 0);
	value = regexec(&regex, name->str, 0, NULL, 0) == 0; 
	return !value;
}

int countLines(string fileName) {

	if(!fileExists(fileName)) return -1;

	FILE* fp = fopen(fileName->str, "r");		

	string dummyString = make_empty_string();	
	size_t stringLength = 0;
	ssize_t readFile;

	int numberOfLines = 0;

	while ((readFile = getline(&(dummyString->str), &stringLength, fp)) != -1) {
		numberOfLines++;
	}
	fclose(fp);

	return numberOfLines;
}