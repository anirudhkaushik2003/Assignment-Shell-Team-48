//used to keep an array of subject names
#include "Subjects.h"
void Initialize_subject_array()
{

    DIR *d;
    struct dirent *dir;
    d = opendir("../Server");

    Server_file_count = 0;

    if (d) //gets us the number of subjects
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                Server_file_count++;
            }
        }

        closedir(d);
    }
    Subject_array = malloc(sizeof(String) * Server_file_count);
    for (int i = 0; i < Server_file_count; i++)
    {
        Subject_array[i].str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    }
    d = opendir("../Server");

    if (d)
    {
        int i = 0;
        while ((dir = readdir(d)) != NULL) 
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                strcpy(Subject_array[i].str, dir->d_name);  //stores the subject name
                Subject_array[i].length = strlen(Subject_array[i].str);

                i++;
            }
        }
        closedir(d);
    }
}
