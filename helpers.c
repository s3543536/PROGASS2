#include "helpers.h"

int parseInt(char* string, int* i) {
	char* stringEndPtr;

	*i = strtol(string, &stringEndPtr, 10);
	if(string == stringEndPtr || *stringEndPtr != '\0') {
		/*printf("NaN\nend: %x\n", *stringEndPtr);*/
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

Boolean getStr(char* s, int size) {
	int i;

	fgets(s, size, stdin);
	strToLower(s);

	for(i = 0; i < size; i++) {
		if(s[i] == '\n') {
			/*printf("checkStr index (\\n): %d\n", i);*/
			s[i] = '\0';/*trim the \n*/
			if(s[0] == '\0')
				return FALSE;
			return TRUE;
		}
	}

	readRestOfLine();
	printf("Input too Long\n");
	s[0] = '\0';
	return FALSE;
}

void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

void strToLower(char* s) {
	int i;
	for(i = 0; i < strlen(s); i++) {
		s[i] = tolower(s[i]);
	}
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

	line = malloc(sizeof(c) * (n+1));
	if(line == NULL) {
		printf("ERROR: malloc gave no memory");
	}
	memset(line, c, sizeof(c) * (n));
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
