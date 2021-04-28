#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
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

