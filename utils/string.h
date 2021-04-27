#ifndef __STRINGLIB
#define __STRINGLIB

typedef struct string *string;

struct string
{
    char *str;
    int size;
};

// basic functions

string make_empty_string();
string copy_string(string dest, string src);
string break_string(string src, int break_len);
string make_string(const char src[]); //makes a input string into newly created string data-type
int compare_string(string str1, string str2);
string delete_string(string x);

// some more important functions

string attach_string(char x[], char y[]);
string convert_to_string(long long int data);

#endif