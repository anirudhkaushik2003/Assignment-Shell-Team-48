#ifndef __STRINGLIB
#define __STRINGLIB

typedef struct String* string;

struct String
{
    char *str;
    int size;
};

// Basic functions

string make_empty_string();
string copy_string(string dest, string src);
string break_string(string src, int break_len);
string make_string(const char src[]); // Makes a input string into newly created string data-type
int compare_string(string str1, string str2);
string delete_string(string x);

// Some more important functions

string attach_string(char x[], char y[]);
string convert_to_string(long long int data);

#endif
