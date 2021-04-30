#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>
#include "files.h"
#include "string.h"

int folderExists(String *path)
{
    struct stat sb;
    return stat(path->str, &sb) == 0 && S_ISDIR(sb.st_mode);
}

int fileExists(String *path)
{
    struct stat sb;
    return stat(path->str, &sb) == 0 && S_ISREG(sb.st_mode);
}

int deleteFile(String *path)
{
    if (!fileExists(path))
    {
        return 0;
    }
    String *command = make_empty_String();
    sprintf(command->str, "rm %s > /dev/null", path->str);
    system(command->str);
    return 1;
}

int deleteFolder(String *path)
{
    if (!folderExists(path))
    {
        return 0;
    }
    String *command = make_empty_String();
    sprintf(command->str, "rm -r %s > /dev/null", path->str);
    system(command->str);
    return 1;
}

int createZip(String *path, String *zipName)
{
    if (!folderExists(path))
    {
        return 0;
    }
    String *command = make_empty_String();
    sprintf(command->str, "zip -r %s.zip %s > /dev/null", zipName->str, path->str);
    system(command->str);
    return 1;
}

int createFolder(String *folder)
{
    if (folderExists(folder))
    {
        return 0;
    }

    String *command = make_empty_String();
    sprintf(command->str, "mkdir %s > /dev/null", folder->str);
    system(command->str);
    return 1;
}
int validFileName(String *name)
{
    String *fileRegex = make_String("[^-_.A-Za-z0-9]");
    // String* fileRegex = make_String*("^(\\w+\\.?)*\\w+$ ");
    regex_t regex;
    int value = regcomp(&regex, fileRegex->str, 0);
    value = regexec(&regex, name->str, 0, NULL, 0) == 0;
    return !value;
}

int countLines(String *fileName)
{

    if (!fileExists(fileName))
        return -1;

    FILE *fp = fopen(fileName->str, "r");

    String *dummyString = make_empty_String();
    size_t StringLength = 0;
    ssize_t readFile;

    int numberOfLines = 0;

    while ((readFile = getline(&(dummyString->str), &StringLength, fp)) != -1)
    {
        numberOfLines++;
    }
    fclose(fp);

    return numberOfLines;
}