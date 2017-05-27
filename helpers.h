#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1

/* its a signed int, so 10 */
#define MAX_ID_LENGTH 10

/**
 * This is used to compensate for the extra character spaces taken up by
 * the '\n' and '\0' when input is read through fgets().
 **/
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

#define EMPTY_STRING ""

/**
 * Call this function whenever you detect buffer overflow.
 **/
void readRestOfLine();

void strToLower(char* s);

int parseInt(char* string, int* i);

Boolean getStr(char* s, int size);

/** creates a line of character c, of length n
 *
 * make sure you free the memory!
 */
char* charLine(char c, int n);

void tokenk(char* str, char* delim, char **tokens, int* tokCount);
char ** h_token(char* str, char* delim);

int maxInt(int a, int b);
int minInt(int a, int b);

#define aCharLine printf
#endif
