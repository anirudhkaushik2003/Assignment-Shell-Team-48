#ifndef __STRING_H__
#define __STRING_H__

#include "../processor/Input.h"
#include "../globals.h"

// Basic functions

String *make_empty_String();
String *copy_String(String *dest, String *src);
String break_String(String src, int break_len);
String *make_String(const char src[]); // Makes a input String into newly created String data-type
int compare_String(String str1, String str2);
String delete_String(String x);

// Some more important functions

String attach_String(char x[], char y[]);
String convert_to_String(long long int data);

#endif
