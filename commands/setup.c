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
int noOfTabs(String fileLine) {
	int tabCount = 0;

	for (int i = 0; i < fileLine.length; i++) {
		if((int)fileLine.str[i] != ASCII_TAB) break; 

		tabCount++;
	}

	return tabCount;
}

// Returns an array of the number of indents on each line of the file
int* countIndents(String fileName, int lines) {

	int* indentCount = (int*)calloc(sizeof(int), lines);

    String* fileLine = make_empty_String();
	size_t lineLength = 0;
	ssize_t fileRead;

	int currLine = 0;
	FILE* fp = fopen(fileName.str, "r");		

    // fileLine will store the line we're dealing with 

	while ((fileRead = getline(&(fileLine->str), &lineLength, fp)) != -1) {
        
        // indentCount stores the indentation of each line
		indentCount[currLine] = noOfTabs(*fileLine);	

        // getline comes with the "\n", which we don't want
		fileLine->length = strlen(fileLine->str);
		fileLine->str[fileLine->length- 1]  = '\0';	
		
        // Skipping the indents in the String to make the folder name
        String* folderName =  make_String(&(fileLine->str[indentCount[currLine]]));

        /* Verifying if the folder name is valid, if not then set 
         * the first line's indent to -1 to indicate invalid naming.
         */
		if(!validFileName(*folderName)) {
			indentCount[0] = -1;
			break;
		}	

		currLine++;

        if (currLine == lines) break;
	}

	fclose(fp);

	return indentCount;
}
void createFileStructure(String fileName,int* indentCount, int lines) {
    String* directory = make_String(".");
	int curr_indent = 0;
	
    String* fileLine = make_empty_String();
	size_t lineLength = 0;
	ssize_t fileRead;
	int curr_line = 0;
	FILE* fp = fopen(fileName.str, "r");		

    String* prev = make_empty_String();
    String* curr = make_empty_String();

	while ((fileRead = getline(&(fileLine->str), &lineLength, fp)) != -1) {
        fileLine->length= strlen(fileLine->str);
        prev = copy_String(prev, curr);
        curr = copy_String(curr, fileLine);

        /* If you're going in one level deep, append the previous folder to the            
         * current directory.
         */
		if (indentCount[curr_line] > curr_indent) {
            directory = attach_String(directory->str, "/");    
            char *previousDirectory = &(prev->str[indentCount[curr_line-1]]);
            directory = attach_String(directory->str, previousDirectory);
			curr_indent++;
		}
        /* If you're going some levels outside of the current directory
         * then delete the appropriate chunk of the current directory path.
         */
		else if (indentCount[curr_line] < curr_indent) {
			directory->length = strlen(directory->str);	
			int required = curr_indent - indentCount[curr_line];
			int count = 0;

			for (int i = directory->length - 1; i >= 0; i--) {
				if (directory->str[i] == '/') count++;
				if (count == required) {
					directory->str[i] = '\0';
					break;
				}
			}
			curr_indent = indentCount[curr_line];
		}

        /* Creating a temporary String to hold the path + the folder
         * that you want to make.
         */
        directory->length = strlen(directory->str);

        String* folderName = make_empty_String();
        folderName = copy_String(folderName, directory);
        folderName = attach_String(folderName->str, "/");

		curr->length = strlen(curr->str);
		curr->str[curr->length - 1] = '\0';

        folderName = attach_String(folderName->str, &(curr->str[indentCount[curr_line]]));
        
        createFolder(*folderName);

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

void setup(String fileName) {

    if (!fileExists(fileName)) {
        printf("%s file doesn't exist\n", fileName.str);
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
