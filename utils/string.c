#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2000

string make_empty_string()
{
    string empty = (string)malloc(sizeof(struct String));

    empty->str = (char *)malloc(sizeof(char) * MAX_LEN);

    empty->size = 1;
    empty->str[0] = '\0';

    return empty;
}

string delete_string(string x)
{
    x->str[0] = '\0';

    x->size = 1;

    return x;
}

string make_string(const char src[])
{
    string data = make_empty_string();

    // data.str = (char *)malloc(sizeof(char) * MAX_LEN);

    data->size = strlen(src) + 1;

    strncpy(data->str, src, data->size);

    return data;
}

string copy_string(string dest, string src)
{
    dest = make_empty_string();
    // dest.str = (char *)malloc(sizeof(char) * MAX_LEN);

    dest->size = src->size;

    strncpy(dest->str, src->str, src->size);

    return dest;
}

int compare_string(string str1, string str2)
{
    long long int i;

    for (i = 0; i < str1->size && i < str2->size; i++)
    {
        if (str1->str[1] != str2->str[i])
        {
            return 0;
        }
    }

    return 1;
}

string break_string(string src, int break_len)
{
    string dest = make_empty_string();

    // dest.str = (char *)malloc(sizeof(char) * MAX_LEN);

    dest->size = break_len + 1;

    strncpy(dest->str, src->str, break_len);

    return dest;
}

string attach_string(char x[], char y[])
{
    string attached;

    attached = make_string(x);

    attached->str = strcat(attached->str, y);

    attached->size = strlen(attached->str) + 1;

    return attached;
}

string convert_to_string(long long int data)
{
    string final = make_empty_string();

    sprintf(final->str, "%lld", data);

    final->size = strlen(final->str) + 1;

    return final;
}
