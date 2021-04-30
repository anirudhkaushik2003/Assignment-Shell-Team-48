#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "../utils/files.h"
#include "../utils/string.h"
#define ASCII_TAB 9


/* Returns the number of tabs the string is indented with,
 * doesn't work on whitespaces, only tabs
 */
int noOfTabs(string fileLine) {
	int tabCount = 0;

	for (int i = 0; i < fileLine->size; i++) {
		if((int)fileLine->str[i] != ASCII_TAB) break; 

		tabCount++;
	}

	return tabCount;
}

// Returns an array of the number of indents on each line of the file
int* countIndents(string fileName, int lines) {

	int* indentCount = (int*)calloc(sizeof(int), lines);

    string fileLine = make_empty_string();
	size_t lineLength = 0;
	ssize_t fileRead;

	int currLine = 0;
	FILE* fp = fopen(fileName->str, "r");		

    // fileLine will store the line we're dealing with 

	while ((fileRead = getline(&(fileLine->str), &lineLength, fp)) != -1) {
        
        // indentCount stores the indentation of each line
		indentCount[currLine] = noOfTabs(fileLine);	

        // getline comes with the "\n", which we don't want
		fileLine->size = strlen(fileLine->str);
		fileLine->str[fileLine->size - 1]  = '\0';	
		
        // Skipping the indents in the string to make the folder name
        string folderName =  make_string(&(fileLine->str[indentCount[currLine]]));

        /* Verifying if the folder name is valid, if not then set 
         * the first line's indent to -1 to indicate invalid naming.
         */
		if(!validFileName(folderName)) {
			indentCount[0] = -1;
			break;
		}	

		currLine++;

        if (currLine == lines) break;
	}

	fclose(fp);

	return indentCount;
}
void createFileStructure(string fileName,int* indentCount, int lines) {
    string directory = make_string(".");
	int curr_indent = 0;
	
    string fileLine = make_empty_string();
	size_t lineLength = 0;
	ssize_t fileRead;
	int curr_line = 0;
	FILE* fp = fopen(fileName->str, "r");		

    string prev = make_empty_string();
    string curr = make_empty_string();

	while ((fileRead = getline(&(fileLine->str), &lineLength, fp)) != -1) {
        fileLine->size = strlen(fileLine->str);
        prev = copy_string(prev, curr);
        curr = copy_string(curr, fileLine);

        /* If you're going in one level deep, append the previous folder to the            
         * current directory.
         */
		if (indentCount[curr_line] > curr_indent) {
            directory = attach_string(directory->str, "/");    
            char *somethign = &(prev->str[indentCount[curr_line-1]]);
            directory = attach_string(directory->str, somethign);
			curr_indent++;
		}
        /* If you're going some levels outside of the current directory
         * then delete the appropriate chunk of the current directory path.
         */
		else if (indentCount[curr_line] < curr_indent) {
			directory->size = strlen(directory->str);	
			int required = curr_indent - indentCount[curr_line];
			int count = 0;

			for (int i = directory->size - 1; i >= 0; i--) {
				if (directory->str[i] == '/') count++;
				if (count == required) {
					directory->str[i] = '\0';
					break;
				}
			}
			curr_indent = indentCount[curr_line];
		}

        /* Creating a temporary string to hold the path + the folder
         * that you want to make.
         */
        directory->size = strlen(directory->str);

        string folderName = make_empty_string();
        folderName = copy_string(folderName, directory);
        folderName = attach_string(folderName->str, "/");

		curr->size = strlen(curr->str);
		curr->str[curr->size - 1] = '\0';

        folderName = attach_string(folderName->str, &(curr->str[indentCount[curr_line]]));
        
        createFolder(folderName);

		curr_line++;
	}	
}

/* CODE returned by validFileStructure()
 * 0 - Valid File Structure
 * 1 - Improper indentation (Eg Current Line is indented 2 times more than the prev line)
 * 2 - Multiple Assignments (More than one line has zero indents, which isn't allowed)
 * 3 - Both 1 and 2 have occurred
 * 4 - If any of the file names are invalid
 */

int validFileStructure(int* arr, int lines) {
	int code = 0;	
	if (arr[0] == -1) {
		code = 4;
	}
	else {
		int flag = arr[0] == 0;
		int onlyZero = 1;
		for (int i = 1; i < lines; i++) {
			flag = flag && ((arr[i] - arr[i - 1]) <= 1);
			onlyZero = onlyZero && (arr[i] != 0);
		}
		code = (flag ? 0 : 1) + (onlyZero ? 0 : 2);
	}
	return code;
}

void setup(string fileName) {

    if (!fileExists(fileName)) {
        printf("%s file doesn't exist\n", fileName->str);
        return;
    }

	int lines = countLines(fileName);
	int* indentCount = countIndents(fileName, lines);
	int code = validFileStructure(indentCount, lines);

	if (code == 4) {
		printf("Invalid folder name/s");
	}
	else if (code == 3) {
		printf("Invalid indenting and multiple assignments specified\n");
	}
	else if (code == 2) {
		printf("You can only create one assignment at a time\n");
	}
	else if (code == 1) {
		printf("Invalid indenting in the file structure\n");
	}	
	else {
		createFileStructure(fileName, indentCount, lines);
	}

	free(indentCount);

}
