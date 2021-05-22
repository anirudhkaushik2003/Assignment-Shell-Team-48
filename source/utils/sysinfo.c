#include "sysinfo.h"

String get_username()//gets the username
{
    String username;
    struct passwd *p = getpwuid(getuid());
    strcpy(username.str, p->pw_name);
    username.length = strlen(username.str);

    return username;
}

String get_pwd() //gets the machine name but this isnt used
{
    if (start_point == 0)
    {
        subj = make_empty_String();
        start_point++;
    }
    String current_path;
    current_path.str = (char *)malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    getcwd(current_path.str, MAX_TOKEN_LENGTH);
    current_path.length = (int)strlen(current_path.str);

    int match = compare_String(current_path, home_path);
    if (match >= home_path.length)
    {
        sprintf(current_path.str, "~%s", home_path.str);
    }
    current_path.length = (int)strlen(current_path.str);
    return current_path;
}

void out_pwd()//unused util
{
    String current_path;
    current_path.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    getcwd(current_path.str, MAX_TOKEN_LENGTH);
    printf("%s", current_path.str);
}