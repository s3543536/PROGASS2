#include "helpers.h"

void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

char* charLine(char c, int n) {
	char* line;
	line = malloc(sizeof(c) * (n+1));
	memset(line, (int)c, sizeof(char) * (n+1));
	line[n] = '\0';
	return line;
}
