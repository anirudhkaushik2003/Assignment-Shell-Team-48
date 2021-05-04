#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 2000

String *make_empty_String()
{
    String *empty;
    empty = malloc(sizeof(String));
    empty->str = malloc(sizeof(char) * 100);

    return empty;
}

String delete_String(String x)
{
    x.str[0] = '\0';

    x.length = 1;

    return x;
}

String *make_String(const char src[])
{
    String *data = make_empty_String();

    // data.str = (char *)malloc(sizeof(char) * MAX_LEN);

    data->length = strlen(src) + 1;

    strncpy(data->str, src, data->length);

    return data;
}

String *copy_String(String *dest, String *src)
{
    dest = make_empty_String();
    // dest.str = (char *)malloc(sizeof(char) * MAX_LEN);

    dest->length = src->length;

    strncpy(dest->str, src->str, src->length);

    return dest;
}

int compare_String(String str1, String str2)
{
    long long int i;

    for (i = 0; i < str1.length && i < str2.length; i++)
    {
        if (str1.str[i] != str2.str[i])
        {
            return i;
        }
    }

    return (int)fmin(str1.length, str2.length);
}

/*String break_String(String src, int break_len)
{
    String dest = make_empty_String();

    // dest.str = (char *)malloc(sizeof(char) * MAX_LEN);

    dest.length = break_len + 1;

    strncpy(dest.str, src.str, break_len);

    return dest;
}

String attach_String(char x[], char y[])
{
    String attached;

    attached = make_String(x);

    attached.str = strcat(attached.str, y);

    attached.length = strlen(attached.str) + 1;

    return attached;
}

String convert_to_String(long long int data)
{
    String final = make_empty_String();

    sprintf(final.str, "%lld", data);

    final.length = strlen(final.str) + 1;

    return final;
}
*/