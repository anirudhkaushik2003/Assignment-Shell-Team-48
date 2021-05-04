#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *str;
    str = malloc(sizeof(char)*100);
    struct passwd *p = getpwuid(getuid());
    strcpy(str,p->pw_name);
    printf("string = %s\n",str);
    strcpy(str,p->pw_dir);
    printf("string = %s\n",str);
}