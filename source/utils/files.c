#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>
#include "files.h"
#include "string.h"

#define MAX_LEN 2000
// Prints an error in rea
void printError(String message) {
    printf("\033[1;31m");
    printf("%s", message.str);
    printf("\033[0m");
}
void printSuccess(String message) {
    printf("\033[0;32m");
    printf("%s", message.str);
    printf("\033[0m");
}
void printWarning(String message) {
    printf("\033[0;33m");
    printf("%s", message.str);
    printf("\033[0m");
}
// Takes in a path and verifies if such a folder exists
int folderExists(String path)
{
	struct stat sb;
	return stat(path.str, &sb) == 0 && S_ISDIR(sb.st_mode);
}

// Takes in a path and verifies if such a file exists
int fileExists(String path)
{
	struct stat sb;
	return stat(path.str, &sb) == 0 && S_ISREG(sb.st_mode);
}

/* Deletes the file specified by the path
 * Returns 0 if it doesn't exist
 * Returns 1 if it does and deletes the file
 */
int deleteFile(String path)
{
	if (!fileExists(path))
	{
		return 0;
	}
	String *command = make_empty_String();
	sprintf(command->str, "rm %s > /dev/null", path.str);
	system(command->str);
	return 1;
}

/* Deletes the folder specified by the path
 * Returns 0 if it doesn't exist
 * Returns 1 if it does and deletes the folder
 */
int deleteFolder(String path)
{
	if (!folderExists(path))
	{
		return 0;
	}
	String *command = make_empty_String();
	sprintf(command->str, "rm -r %s > /dev/null", path.str);
	system(command->str);
	return 1;
}

/* Zips a folder specified by path
 * Returns 0 if the folder doesn't exist
 * Returns 1 if the folder exists and you create a zip with the name as zipName
 */
int createZip(String path, String zipName)
{
	if (!folderExists(path))
	{
		return 0;
	}
	String *command = make_empty_String();
	sprintf(command->str, "zip -r %s.zip %s > /dev/null", zipName.str, path.str);
	system(command->str);
	return 1;
}

/* Unzips a zip file to a path specified
 * Returns 0 if the zip files doesn't exist
 * Returns 1 if it does and is unzipped
 */
int unzipToDirectory(String zipName, String path)
{
	if (!fileExists(zipName))
	{
		return 0;
	}
	String *command = make_empty_String();
	sprintf(command->str, "unzip %s -d %s > /dev/null", zipName.str, path.str);
	system(command->str);
	return 1;
}

/* Creates a folder at path specified
 * Returns 0 if the folder already exists
 * Else it returns 1 and creates the folder
 */
int createFolder(String folder)
{
	if (folderExists(folder))
	{
		return 0;
	}

	String *command = make_empty_String();
	sprintf(command->str, "mkdir %s > /dev/null", folder.str);
	system(command->str);
	return 1;
}
/* Uses regex to verify if the given name is a valid file name
 * We've restricted the file names intentionally, so you might be able to make
 * file names with some symbols normally but wouldn't pass validFileName as we only want
 * more standard symbols for files to be permitted
 */
int validFileName(String name)
{
	String *fileRegex = make_String("[^-_.A-Za-z0-9]");
	regex_t regex;
	int value = regcomp(&regex, fileRegex->str, 0);
	value = regexec(&regex, name.str, 0, NULL, 0) == 0;
	return !value;
}

// Opens a file and returns the number of lines in it, returns -1 if it doesn't exist
int countLines(String fileName)
{

	if (!fileExists(fileName))
		return -1;

	FILE *fp = fopen(fileName.str, "r");

	String *dummyString = make_empty_String();
	size_t stringLength = 0;
	ssize_t readFile;

	int numberOfLines = 0;

	while ((readFile = getline(&(dummyString->str), &stringLength, fp)) != -1)
	{
		numberOfLines++;
	}
	fclose(fp);

	return numberOfLines;
}

/* This function gets the name of the subject you are 
	currently present in, it really helps in getting subject
 	at any point of the program
*/
String *getCurrentSubject()
{
	String *homePath;
	homePath = make_empty_String();

	getcwd(homePath->str, MAX_LEN);
	int strLen = strlen(homePath->str);
	String *currSubject = make_empty_String();

	char *token;
	token = strtok(homePath->str, "/");
	String *prev = make_empty_String();

	if (isInSubject)
	{
		while (token != NULL)
		{
			strcpy(prev->str, token);
			token = strtok(NULL, "/");
		}
	}

	for (int i = 0; i < Server_file_count; i++)
	{
		if (strcmp(prev->str, Subject_array[i].str) == 0)
			return prev;
	}

	strcpy(prev->str, "");
	return prev;
}

// Enters the subject directory when you start the shell
void enterSubjectDirectory()
{
	chdir("Subjects");
	printf("Enter switch <subject_name> to begin\n");
}

/* This function checks if the submission folder exists
	under the assignment folder in the server , if it
	doesn't exists then creates one else returns back
*/
void IFsubmission_folder(String assignment_folder, String *zipfile)
{
	String *submission_folder;

	submission_folder = make_String("../../Server/");
	submission_folder = attach_String(submission_folder->str, getCurrentSubject()->str);
	submission_folder = attach_String(submission_folder->str, "/");
	submission_folder = attach_String(submission_folder->str, assignment_folder.str);
	submission_folder = attach_String(submission_folder->str, "/submissions");

	if (!folderExists(*submission_folder))
	{
		createFolder(*submission_folder);
	}
}

/* This function at first checks if the zip file exists in the submissions 
	folder under assignment folder in respective subject of server, If no 
	then it simply copies the zip file of assignment into that else 
	it gives us a prompt to either Overwrite it or Return as it. 
*/
int copy_to_server(String *zipfile, String assignment_folder)
{
	String *home_path = make_empty_String();

	getcwd(home_path->str, MAX_LEN);

	String *path = make_empty_String();
	path->str = "../../Server/";

	path = attach_String(path->str, getCurrentSubject()->str);
	path = attach_String(path->str, "/");
	path = attach_String(path->str, assignment_folder.str);
	path = attach_String(path->str, "/submissions/");

	path = attach_String(path->str, zipfile->str);

	if (fileExists(*zipfile))
	{
		while (1)
		{
			String *prompt = make_empty_String();
			printf("\n\tThe zip file already exists!\n\tEnter Overwrite to replace existing file or Return to leave as it is: ");
			int i = 0;
			char temp;
			while (1)
			{
				temp = (char)getchar();
				if (temp != '\n')
					prompt->str[i++] = temp;
				else
				{
					prompt->str[i] = '\0';
					break;
				}
			}
			
			// On selecting "Overwrite", it deletes the previously existing zip fle and copies the new one there
			if (strcmp(prompt->str, "Overwrite") == 0)
			{
				deleteFile(*path);
				String *command = make_empty_String();

				sprintf(command->str, "cp %s %s > /dev/null", zipfile->str, path->str);
				system(command->str);
				return 1;
			}
			/*On selecting "Return" , it just returns back , keeping the previously
			  existing folder safe.
            */
			else if (strcmp(prompt->str, "Return") == 0)
			{
				return 0;
			}
			else
			{

				String* error = make_String("\n\tERROR: Wrong Command, please enter again!\n\n");
                printError(*error);
			}
		}
	}
	else
	{
		String *command = make_empty_String();

		sprintf(command->str, "cp %s %s > /dev/null", zipfile->str, path->str);

		system(command->str);
		return 1;
	}
}

void clearScreen() {
    system("clear");
}

