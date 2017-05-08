void token(char* str, char* delim, char **tokens, int* tokCount) {
	int max = *tokCount;/*make tokCount the max number of tokens*/
	*tokCount = 0;
	/*tokenise the string*/
	tokens[0] = strtok(str, &*delim);
	
	while(tokens[*tokCount] != NULL && *tokCount < max) {
		(*tokCount)++;
		tokens[*tokCount] = strtok(NULL, &*delim);
		/* *(tokens + tokCount) should also work */
	}
}
