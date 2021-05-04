#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define LENGTH 1000
typedef struct Input input;
struct Input
{
    char *input;
    int input_length;
};
void tokenizer(char *args[100])
{
    execvp(args[0], args);
}
int fileExists(char *path)
{
    struct stat sb;
    return stat(path, &sb) == 0 && S_ISREG(sb.st_mode);
}
int deleteFile(char *path)
{
    if (!fileExists(path))
    {
        return 0;
    }
    char command[100];
    sprintf(command, "rm %s > /dev/null", path);
    system(command);
    return 1;
}
int folderExists(char *path)
{
    struct stat sb;
    return stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);
}
int createZipName(char *path, char *zipName)
{
    if (!folderExists(path))
    {
        //printf("Assignment \"%s\" doesn't exist", path);
        return 0;
    }
    char command[100];
    sprintf(command, "zip -r %s.zip %s > /dev/null", zipName, path);
    system(command);
    return 1;
}
int verifyIntegrity(char *folder, char *file)
{
    char command[100];
    // Create a temporary zip file of the current state of the folder

    createZipName(folder, "temporaryMD5Check");

    // Calculate the md5sum of the zip we are comparing and the zip we just created
    // And output it to a file
    sprintf(command, "md5sum temporaryMD5Check.zip %s > hashCheck.md5", file);
    system(command);

    // Delete the temporary zip file we created since we only needed it to compare md5sum;
    deleteFile("temporaryMD5Check.zip");

    // Compare the two hashvalues

    char a[100], b[100], c[100], d[100];
    FILE *fp = fopen("hashCheck.md5", "r");

    fscanf(fp, "%s %s %s %s", a, b, c, d);

    deleteFile("hashCheck.md5");
    // Returns true if they are equal, false if otherwise
    return strcmp(a, c) == 0;
}
int createZip(char *path)
{
    return createZipName(path, path);
}
int main()
{
    input *home_path;
    input *server_path;
    home_path = malloc(sizeof(input));
    home_path->input = malloc(sizeof(char) * LENGTH);

    server_path = malloc(sizeof(input));
    server_path->input = malloc(sizeof(char) * LENGTH);

    getcwd(home_path->input, LENGTH);
    printf("CWD = %s\n", home_path->input);

    strcpy(server_path->input, home_path->input);
    strcat(server_path->input, "/server/dsa/");

    getcwd(home_path->input, LENGTH);
    printf("CWD = %s\n", home_path->input);
    input *token1;
    token1 = malloc(sizeof(input));
    char *com_value;
    //char *input;
    token1->input = (char *)malloc(sizeof(char) * LENGTH);
    int i = 0;
    char temp;
    com_value = (char *)malloc(sizeof(char) * LENGTH);
    char *args[100];
    while (1)
    {
        i = 0;
        while (1)
        {
            temp = (char)getchar();
            if (temp != '\n')
                com_value[i++] = temp;
            else
                break;
        }
        strcpy(token1->input, com_value);
        token1->input_length = strlen(token1->input) + 1; //includes NULL characyer + new_line character
        printf("com_value = %s\n", com_value);
        printf("input = %s\n", token1->input);
        printf("length of input = %d\n", token1->input_length);
        char *token;
        token = strtok(token1->input, " ");
        i = 0;

        if (strcmp(token, "create") == 0)
        {
            strcpy(token, "mkdir");
        }
        if (strcmp(token, "cd") == 0)
        {
            //cd()
        }
        if (strcmp(token, "submit") == 0)
        {
            token = strtok(NULL, " ");
            chdir("dsa");
            createZip(token);
        }
        if (strcmp(token, "delete") == 0)
        {
            strcpy(token, "rmdir");
        }
        if (strcmp(token, "update") == 0)
        {
            strcpy(token, "cp");
            for (int i = 0; i < 4; i++)
            {
                args[i] = malloc(sizeof(char) * 1000);
            }
            strcpy(args[0], token);
            token = strtok(NULL, " ");
            char *temp = malloc(sizeof(char) * 1000);
            strcpy(temp, server_path->input);
            strcat(temp, token);
            strcpy(args[1], temp);
            args[2] = ".";
            args[3] = NULL;
            //printf("cp call : %s\n", args[1]);
            execvp(args[0], args);
            char *temp2 = malloc(sizeof(char) * 1000);
            for (int i = 0; i < 3; i++)
            {
                strcat(temp2, args[i]);
                strcat(temp2, " ");
            }
            printf("Command : %s\n", temp2);
            system(temp2);
        }
        if (strcmp(token, "switch") == 0)
        {
            token = strtok(NULL, " ");
            chdir(token);
            getcwd(home_path->input, LENGTH);
            printf("CWD = %s\n", home_path->input);
        }
        if (strcmp(token, "compare") == 0)
        {
            chdir("dsa");
            token = strtok(NULL, " ");
            char *temp = malloc(sizeof(char) * LENGTH);
            strcpy(temp, token);
            token = strtok(NULL, " ");
            int a = verifyIntegrity(temp, token);
            if (a == 1)
            {
                printf("The integrity is maintained\n");
            }
            else
            {

                printf("The integrity is not maintained\n");
            }
        }
        if (strcmp(token, "quit") == 0)
        {
            exit(0);
        }

        while (token != NULL)
        {

            args[i] = malloc(sizeof(char) * 100);
            strcpy(args[i], token);
            printf("%s\n", token);
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = malloc(sizeof(char) * 100);
        args[i] = token;

        //char *args[] = {"mkdir", "tester", NULL};

        //free(args);
        tokenizer(args);
    }
}
/*void cd(input path)
{
    // Storing the previous path for cd -
    if (path.input_length == 1 && path.input[0] == '-')
    {
        chdir(prev_path.c_str);
    }
    prev_path.c_str = (char *)calloc(MAX_PATH_LENGTH, 1);
    getcwd(prev_path.c_str, MAX_PATH_LENGTH);
    prev_path.length = (int)strlen(prev_path.c_str);
    // CD flags and path changes
    if (path.length == 1 && path.c_str[0] == '~')
    {
        chdir(home_path.c_str);
    }
    else if (path.length >= 2 && path.c_str[0] == '~' && path.c_str[1] == '/')
    {
        chdir(home_path.c_str);
        chdir(path.c_str + 1);
    }
    else if (path.c_str[0] != '-')
    {
        chdir(path.c_str);
    }
}*/
