#include "sysinfo.h"

String get_username()
{
    String username;
    struct passwd *p = getpwuid(getuid());
    strcpy(username.str, p->pw_name);
    username.length = strlen(username.str);

    return username;
}

String get_machine_name()
{
    int fd = open("/proc/sys/kernel/hostname", O_RDONLY);
    String name;
    name.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    getcwd(name.str, MAX_TOKEN_LENGTH);
    name.length = (int)strlen(name.str);
    if (fd < 0)
    {
        name.length = 11;
        name.str = "UNK-machine";
    }
    else
    {
        name.length = read(fd, name.str, 100);
        name.str[name.length - 1] = 0;
    }
    close(fd);
    return name;
}
String get_pwd()
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

void out_pwd()
{
    String current_path;
    current_path.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    getcwd(current_path.str, MAX_TOKEN_LENGTH);
    printf("%s", current_path.str);
}