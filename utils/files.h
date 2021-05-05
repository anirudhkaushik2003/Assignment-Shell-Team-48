#ifndef __FILES_H__
#define __FILES_H__
#include "string.h"

int folderExists(String path);	
int fileExists(String path);

int deleteFile(String path);
int deleteFolder(String path);

int createZip(String path, String zipName);

int validFileName(String name);
int countLines(String fileName);
int createFolder(String folder); 

void enterSubjectDirectory();

String* getCurrentSubject();
#endif

