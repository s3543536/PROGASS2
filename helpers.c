#include "helpers.h"

void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

int maxInt(int a, int b) {
	a -= b;
	a &= (~a) >> 31;
	a += b;
	return a;
}

int minInt(int a, int b) {
	a -= b;
	a &= a >> 31;
	a += b;
	return a;
}

char* charLine(char c, int n) {
	char* line;
	
	if(n < 1)
		printf("\tERROR: making line with %d of %c\n", n, c);
	line = malloc(sizeof(c) * (n+6));
	memset(line, (int)c, sizeof(c) * (n+1));
	line[n] = '\0';
	return line;
}

void printCharLine(char c, int n) {
	char* line = charLine(c, n);
	printf("%s\n", line);
	free(line);
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

	/* if previous is not null, increment and do next */
	while(tokens[tokIdx++] != NULL) {
		/* grow tokens array */
		tokens = realloc(tokens, sizeof(*tokens) * (tokIdx+1));
		/* set new spot to contain pointer */
		tokens[tokIdx] = strtok(NULL, delim);
		/*printf("tokIdx: %d\n", tokIdx);*/
	}

	return tokens;
}
