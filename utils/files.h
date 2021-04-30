#ifndef FILES_LIB
#define FILES_LIB
#include "string.h"

int folderExists(string path);	
int fileExists(string path);

int deleteFile(string path);
int deleteFolder(string path);

int createZip(string path, string zipName);

int validFileName(string name);
int countLines(string fileName);
int createFolder(string folder); 

#endif

