#ifndef __STRING_H__
#define __STRING_H__

#include "../processor/input.h"
#include "../globals.h"

// Basic functions

String *make_empty_String();
String *copy_String(String *dest, String *src);
String *break_String(String src, int break_len);
String *make_String(const char src[]); 
int compare_String(String str1, String str2);
String erase_String(String x);

// utility function 

String *attach_String(char x[], char y[]);

#endif