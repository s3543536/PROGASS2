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

void token(char* str, char* delim, char **tokens, int* tokCount) {
	int max = *tokCount;/*make tokCount the max number of tokens*/
	*tokCount = 0;
	/*tokenise the string*/
	tokens[0] = strtok(str, delim);
	
	while(tokens[*tokCount] != NULL && ++(*tokCount) < max) {
		tokens[*tokCount] = strtok(NULL, delim);
	}
}

/* input str and delim, token function creates **tokens */
char ** h_token(char* str, char* delim) {
	char ** tokens;
	int tokIdx = 0;

	/* setup array */
	tokens = malloc(sizeof(*tokens));
	/*printf("sizeof(*tokens): %d\n", (int)sizeof(*tokens));*/

	/* start strtok */
	tokens[0] = strtok(str, delim);

	/* do each token */
	while(tokens[tokIdx++] != NULL) {
		tokens = realloc(tokens, sizeof(*tokens) * (tokIdx+1));
		tokens[tokIdx] = strtok(NULL, delim);
		/*printf("tokIdx: %d\n", tokIdx);*/
	}

	return tokens;
}
