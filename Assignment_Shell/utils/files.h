#ifndef FILES_LIB
#define FILES_LIB
#include "string.h"

int folderExists(String *path);
int fileExists(String *path);

int deleteFile(String *path);
int deleteFolder(String *path);

int createZip(String *path, String *zipName);

int validFileName(String *name);
int countLines(String *fileName);
int createFolder(String *folder);

#endif