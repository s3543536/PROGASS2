#include "commands.h"

/**
 * Note this file is to contain console output,
 * meaning printf's are expected to be seen in this file.
 */



Boolean validatePhoneNumber(char * number) {
	return TRUE;/* TODO */
}

/* 
 * checks each token
 *
 * the last pointer in the array is set to NULL
 */
Boolean validateLine(char ** tokens) {
	int i;

	/* make sure the id and name fields exist */
	if(tokens[0] == NULL)
		return FALSE;
	if(tokens[1] == NULL)
		return FALSE;

	/* validate id TODO*/

	/* validate name TODO*/

	i = 2;/* phone numbers start at 2 for this file format */
	while(tokens[i] != NULL) {
		/* validate each phone number */
		if(!validatePhoneNumber(tokens[i])
			return FALSE;
		i++;
	}

	/* all tests passed */
	return TRUE;
}

void printToks(char ** toks) {
	int i = 0;

	while(toks[i] != NULL) {
		printf("%-11s", toks[i]);
		i++;
	}
	printf("\n");
}

AddressBookList * commandLoad(char * fileName)
{
    /**
     * Loads the given file and returns a new AddressBookList.
     * 
     * If the file doesn't exist or corruption is found in the file
     * then NULL is returned.
     */
/*
	AddressBookList *list;
	AddressBookNode *node;
	char *line[MAX_LINE_LENGTH];
	FILE * fp;

	list = createAddressBookList();

	..read from file
	..skip line with #
	..tokenise the line
	..id , name

	...the create array is called in this function VVV
	node = createAddressBookNode();
	continue tokenise line for telephones
		addTelephone(node->array, telephone);
	insertNode(list, node);*/
	AddressBookList * adb;
	AddressBookNode * node;
	FILE * file;
	int size = MAX_LINE_LENGTH + NULL_SPACE;
	char * line = malloc(sizeof(*line) * size);
	char ** tokens;
	int id;
	char* endptr;
	int i;

	printf("\nloading...\n");
	adb = createAddressBookList();

	file = fopen(fileName, "r");
	while(fgets(line, size, file)) {
		/* remove comments */
		if(line[0] == '#')
			continue;

		/* remove \n */
		strtok(line, "\n");

		printf("\nline:   %s\n", line);

		/* token line */
		tokens = h_token(line, ",");

		/*printf("tokens: %-4s%-20s%-11s\n", tokens[0], tokens[1], tokens[2]);*/
		printf("tokens: ");
		printToks(tokens);

		/* validate tokens */
		if(!validateLine(tokens)) {
			printf("File: %s is Corrupt", fileName);
			fclose(file);
			return NULL;
		}

		/* insert tokens into node */
		id = strtol(tokens[0], &endptr, 10);
		node = createAddressBookNode(id, tokens[1]);
		
		/* insert telephone numbers */
		i = TEL_IDX;
		while(tokens[i] != NULL) {
			addTelephone(node->array, tokens[i]);
			i++;
		}

		/* insert node into list */
		insertNode(adb, node);

		free(tokens);
	}
	fclose(file);
	free(line);

    return adb;
}

void commandUnload(AddressBookList * list)
{ }

void commandDisplay(AddressBookList * list)
{ }

void commandForward(AddressBookList * list, int moves)
{ }

void commandBackward(AddressBookList * list, int moves)
{ }

void commandInsert(AddressBookList * list, int id, char * name, char * telephone)
{ }

void commandAdd(AddressBookList * list, char * telephone)
{ }

void commandFind(AddressBookList * list, char * name)
{ }

void commandDelete(AddressBookList * list)
{ }

void commandRemove(AddressBookList * list, char * telephone)
{ }

void commandSort(
    AddressBookList * list,
    int sort(const void * node, const void * otherNode))
{
    /* Sort the nodes within list in ascending order using the
     * provided sort function to compare nodes.
     */
}

int compareName(const void * node, const void * otherNode)
{
    /* Compare node name with otherNode name.
     * 
     * return < 0 when node name is smaller than otherNode name.
     * return 0 when the names are equal.
     * return > 0 when node name is bigger than otherNode name.
     */
    return 0;
}

int compareID(const void * node, const void * otherNode)
{
    /* Compare node id with otherNode id.
     * 
     * return < 0 when node id is smaller than otherNode id.
     * return 0 when the ids are equal.
     * return > 0 when node id is bigger than otherNode id.
     */
    return 0;
}

void commandSave(AddressBookList * list, char * fileName)
{ }
