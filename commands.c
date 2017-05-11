#include "commands.h"

/**
 * Note this file is to contain console output,
 * meaning printf's are expected to be seen in this file.
 */



void printToks(char ** toks) {
	int i = 0;

	do {
		printf("%-11s", toks[i]);
	} while(toks[i++] != NULL);
	printf("\n");
}

int validatePhoneNumber(char * number) {
	char* endptr = NULL;

	if(strlen(number) != TELEPHONE_LENGTH - NULL_SPACE)
		return FALSE;

	/* try to convert to int */
	strtol(number, &endptr, 10);

	/* endpointer gets set if it can't validate */
	if(endptr != NULL && *endptr != 0)
		return FALSE;

	return TRUE;
}

/* 
 * checks each token
 *
 * the last pointer in the array is set to NULL
 */
Boolean validateLine(char ** tokens) {
	int i;
	int id;
	char* endptr = NULL;
	int namelen;

	/* make sure the id and name fields exist */
	if(tokens[0] == NULL)
		return FALSE;
	if(tokens[1] == NULL)
		return FALSE;

	/* validate id */
	id = strtol(tokens[0], &endptr, 10);
	if(endptr != NULL && *endptr != 0) {
		printf("end pointer: |%s|%d|\n", endptr, (int)*endptr);
		return FALSE;
	}
	if(id < NODE_MINIMUM_ID)
		return FALSE;

	/* validate name */
	namelen = strlen(tokens[1]);
	if(namelen > NAME_LENGTH || namelen <= 0)
		return FALSE;

	i = 2;/* phone numbers start at 2 for this file format */
	while(tokens[i] != NULL) {
		/* validate each phone number */
		if(!validatePhoneNumber(tokens[i]))
			return FALSE;
		i++;
	}

	/* all tests passed */
	return TRUE;
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
	char* endptr = NULL;
	int i;
	int count = 0;
	int err_line_count = 0;

	adb = createAddressBookList();

	printf("opening the file: %s\n", fileName);
	file = fopen(fileName, "r");
	printf("loading...\n");
	while(fgets(line, size, file)) {
		err_line_count++;
		/* remove comments */
		if(line[0] == '#')
			continue;

		/* remove \n */
		strtok(line, "\n");

		/*printf("\nline:   %s\n", line);*/

		/* token line */
		tokens = h_token(line, ",");

		/* validate tokens */
		if(!validateLine(tokens)) {
			printf("File: %s is Corrupt\nat line: %d\n", 
					fileName, err_line_count);
			fclose(file);
			free(line);
			free(tokens);
			freeAddressBookList(adb);
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
		count++;
	}
	printf("closing the file\n");
	fclose(file);

	free(line);
	printf("%d phone book entries have been loaded from %s\n", count, fileName);
    return adb;
}

void commandUnload(AddressBookList * list)
{
	freeAddressBookList(list);
}

int getLongestName(AddressBookList * list) {
	AddressBookNode * node = list->head;
	int length = 0;

	while(node != NULL) {
		length = maxInt(length, strlen(node->name));
		node = node->nextNode;
	}
	return maxInt(length, strlen("Name"));
}

int getLongestID(AddressBookList * list) {
	AddressBookNode * node = list->head;
	int maxID = 0;
	char numStr[MAX_ID_LENGTH + NULL_SPACE];

	while(node != NULL) {
		maxID = maxInt(maxID, node->id);
		node = node->nextNode;
	}

	sprintf(numStr, "%d", maxID);

	return maxInt(strlen(numStr), strlen("ID"));
}

#define POSLEN 3
#define SERIALLEN 6
#define TELEPHONELEN 10

/* " | " * 4
   "| "
   " |"
*/
#define SPACINGLEN 16

void commandDisplay(AddressBookList * list) {
	int serial = 0;
	AddressBookNode * node = list->head;
	int nameLen = getLongestName(list);
	int idLen = getLongestID(list);
	int headerLen = nameLen+POSLEN+SERIALLEN+idLen+TELEPHONELEN+SPACINGLEN;
	char * posStr = "";
	char * phones;

	printCharLine('-', headerLen);
	printf("| Pos | Serial | %-*s | %-*s | Telephone  |\n", 
			idLen, "ID", 
			nameLen, "Name");
	printCharLine('-', headerLen);

	if(node == NULL) {
		/* print empty line */
		printf("| %*s |\n", headerLen - 4, "");
	} else {
		while(node != NULL) {
			serial++;
			if(node == list->current)
				posStr = "CUR";
			else
				posStr = "";

			phones = h_concatPhones(node->array);
			printf("| %-*s | %-*d | %-*d | %-*s | %s\n",
					POSLEN, posStr,
					SERIALLEN, serial,
					idLen, node->id,
					nameLen, node->name,
					phones);
			free(phones);

			node = node->nextNode;
		}
	}
	printCharLine('-', headerLen);
	printf("| Total phone book entries: %-*d |\n", 
			headerLen - (int)strlen("| Total phone book entries:  |"), 
			serial);
	printCharLine('-', headerLen);
}

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

int partsize(Part *part) {
	AddressBookNode *curr = part->head;
	int i = 0;

	if(part->head == NULL)
		return 0;

	do {
		if(curr == NULL) {
			printf("WARNING: Broken List\n");
			return -1;/* broken list */
		}
		curr = curr->nextNode;
		i++;
	} while(curr != part->tail);
	return i;
}

Boolean moveBefore(AddressBookNode * pos, AddressBookNode * toMove, Part * part) {
	printf("putting %s before %s\t", toMove->name, pos->name);
	printf("\t%s was before %s\t\n", toMove->previousNode->name, toMove->name);
	/* stitch up toMove */
	if(toMove->nextNode == NULL) {
		/* at tail */
		part->tail = toMove->previousNode;/* make tail work */
		toMove->previousNode->nextNode = NULL;
	} else if(toMove->previousNode == NULL) {
		/* at head */
		part->head = toMove->nextNode;/* make head work */
		toMove->nextNode->previousNode = NULL;
	} else {
		/* in middle */
		toMove->nextNode->previousNode = toMove->previousNode;
		toMove->previousNode->nextNode = toMove->nextNode;
	}
	/* edit toMove ptrs */
	toMove->nextNode = pos;
	toMove->previousNode = pos->previousNode;/* this works at head too*/
	/* edit toMove surroundings ptrs */
	if(pos->previousNode == NULL) {
		/* at head */
		part->head = pos;/* make head work */
		pos->previousNode = toMove;
	} else {
		/* in middle */
		pos->previousNode->nextNode = toMove;
		pos->previousNode = toMove;
	}
	return TRUE;
}

/**
 * this assumes nodea comes before nodeb
 */
int nodeDiff(AddressBookNode * nodea, AddressBookNode * nodeb) {
	int i = 0;

	while(nodeb != nodea) {
		nodeb = nodeb->previousNode;
		i++;
		if(i > 22) {
			printf("ERROR: nodediff looped too many times");
			return -1;
		}
	}

	return i;
}

void commandSort(
    AddressBookList * list,
    int sort(const void * node, const void * otherNode))
{
    /* Sort the nodes within list in ascending order using the
     * provided sort function to compare nodes.
     */
	Part * parts;
	int partsize = 0;
	Part * currpart;
	AddressBookNode * pivot;
	AddressBookNode * currnode;
	AddressBookNode * nextnode;
	int sortInt;
	int diffa;
	int diffb;

	int a;
	int b;

	/* allocate first parition */
	parts = malloc(sizeof(*parts) * ++partsize);
	parts[0].head = list->head;
	parts[0].tail = list->tail;

	a = 0;
	while(partsize > 0) {
		printf("a%d\n", a++);
		/* choose part */
		currpart = &parts[partsize-1];/* last part */
		/* choose pivot */
		pivot = currpart->head;
		/* sort around pivot (its a linked list so pivot can be the wall) */
		currnode = currpart->head;
		nextnode = currnode->nextNode;
		do {
			currnode = nextnode;
			if(nextnode != NULL) {
				nextnode = nextnode->nextNode;
			}
			sortInt = sort(currnode, pivot);
			if(sortInt < 0) {
				/* currnode is less than pivot */
				if(!moveBefore(pivot, currnode, currpart))
					printf("can't move currnode before pivot\n");
			}
		} while(nextnode != NULL);

		/* grow part array */
		diffa = nodeDiff(currpart->head, pivot);
		diffb = nodeDiff(pivot, currpart->tail);
		
		if(diffa > 1 && diffb > 1) {
			/* grow array */
			parts = realloc(parts, sizeof(*parts) * ++partsize);
			parts[partsize-2].head = currpart->head;
			parts[partsize-2].tail = pivot->previousNode;

			parts[partsize-1].head = pivot->nextNode;
			parts[partsize-1].tail = currpart->tail;
		} else if(diffa > 1) {
			/* array stays the same */
			parts[partsize-1].head = currpart->head;
			parts[partsize-1].tail = pivot->previousNode;
		} else if(diffb > 1) {
			/* array stays the same */
			parts[partsize-1].head = pivot->nextNode;
			parts[partsize-1].tail = currpart->tail;
		} else {
			/* shrink array */
			--partsize;
			if(partsize == 0)
				free(parts);
			else
				parts = realloc(parts, sizeof(*parts) * partsize);
		}
	}
}

int compareName(const void * node, const void * otherNode)
{
    /* Compare node name with otherNode name.
     * 
     * return < 0 when node name is smaller than otherNode name.
     * return 0 when the names are equal.
     * return > 0 when node name is bigger than otherNode name.
     */
	return strcmp(((AddressBookNode*)node)->name, 
			((AddressBookNode*)otherNode)->name);
}

int compareID(const void * node, const void * otherNode)
{
    /* Compare node id with otherNode id.
     * 
     * return < 0 when node id is smaller than otherNode id.
     * return 0 when the ids are equal.
     * return > 0 when node id is bigger than otherNode id.
     */
	return ((AddressBookNode*)node)->id - ((AddressBookNode*)otherNode)->id;
}

void commandSave(AddressBookList * list, char * fileName)
{ }
