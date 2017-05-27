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

/* validates input file format
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

AddressBookList * commandLoad(char * fileName, AddressBookList * adb)
{
    /**
     * Loads the given file and returns a new AddressBookList.
     * 
     * If the file doesn't exist or corruption is found in the file
     * then NULL is returned.
     */
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

	if(adb->size > 0) {
		printf("list is already loaded...\nmake sure to unload first\n");
		return adb;
	}

	printf("opening the file: %s\n", fileName);
	file = fopen(fileName, "r");
	if(file == NULL) {
		printf("file %s not found\n", fileName);
		free(line);
		return adb;
	}

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
			freeAddressBookContents(adb);
			return adb;
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
	freeAddressBookContents(list);
	printf("your list is unloaded\n");
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

void commandDisplayV(AddressBookList * list) {
	int serial = 0;
	AddressBookNode * node = list->head;
	int nameLen = getLongestName(list);
	int idLen = getLongestID(list);
	int headerLen = nameLen+POSLEN+SERIALLEN+idLen+TELEPHONELEN+SPACINGLEN;
	char * posStr = "";
	char * phones;
	char* prevname;
	char* nextname;
	char* line;

	line = charLine('-', headerLen);
	printf("%s\n", line);
	printf("| Pos | Serial | %-*s | %-*s | Telephone  |\n", 
			idLen, "ID", 
			nameLen, "Name");
	printf("%s\n", line);

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

			if(node->nextNode != NULL) {
				nextname = node->nextNode->name;
			} else {
				nextname = NULL;
			}

			if(node->previousNode != NULL) {
				prevname = node->previousNode->name;
			} else {
				prevname = NULL;
			}

			printf("| %-*s | %-*d | %-*d | %-*s | %-50s\t%s\t%s\n",
					POSLEN, posStr,
					SERIALLEN, serial,
					idLen, node->id,
					nameLen, node->name,
					phones,
					nextname,
					prevname);
			free(phones);

			node = node->nextNode;
		}
	}
	printf("%s\n", line);
	printf("| Total phone book entries: %-*d |\n", 
			headerLen - (int)strlen("| Total phone book entries:  |"), 
			serial);
	printf("%s\n", line);
	free(line);
}

void commandDisplay(AddressBookList * list) {
	int serial = 0;
	AddressBookNode * node = list->head;
	int nameLen = getLongestName(list);
	int idLen = getLongestID(list);
	int headerLen = nameLen+POSLEN+SERIALLEN+idLen+TELEPHONELEN+SPACINGLEN;
	char * posStr = "";
	char * phones;
	char * line;

	line = charLine('-', headerLen);
	printf("%s\n", line);
	printf("| Pos | Serial | %-*s | %-*s | Telephone  |\n", 
			idLen, "ID", 
			nameLen, "Name");
	printf("%s\n", line);

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
	printf("%s\n", line);
	printf("| Total phone book entries: %-*d |\n", 
			headerLen - (int)strlen("| Total phone book entries:  |"), 
			serial);
	printf("%s\n", line);
	free(line);
}

void commandForward(AddressBookList * list, int moves) {
	if(list->size < 1) {
		printf("no list\n");
	}
	while(list->current != NULL && moves > 0) {
			list->current = list->current->nextNode;
			moves--;
	}
	if(list->current == NULL)
		list->current = list->tail;
}

void commandBackward(AddressBookList * list, int moves) {
	if(list->size < 1) {
		printf("no list\n");
	}
	while(list->current != NULL && moves > 0) {
		list->current = list->current->previousNode;
		moves--;
	}
	if(list->current == NULL)
		list->current = list->head;
}

void commandInsert(AddressBookList * list, int id, char * name, char * telephone)
{ }

void commandAdd(AddressBookList * list, char * telephone) {
	/* check for empty list */
	if(list->size < 1) {
		printf("phone book is empty, can't add a phone number\n");
		return;
	}

	/* add number */
	if(!addTelephone(list->current->array, telephone)) {
		printf("Can't add telehphone\n");
	}
}

void commandFind(AddressBookList * list, char * name)
{ }

void commandDelete(AddressBookList * list) {

	if(deleteCurrentNode(list)) {
		printf("Current node deleted\n");
	} else {
		printf("node not deleted\n");
	}
}

void commandRemove(AddressBookList * list, char * telephone) {
	/* check for empty list */
	if(list->size < 1) {
		printf("phone book is empty, can't remove a phone number\n");
		return;
	}

	/* remove number */
	if(!removeTelephone(list->current->array, telephone)) {
		printf("Can't remove telephone\n");
	}
}

int partsize(Part *part) {
	AddressBookNode *curr = part->head;
	int i = 0;

	if(part->head == NULL)
		return 0;

	do {
		if(curr == NULL) {
			printf("\t\tERROR: Broken List\n");
			return -1;/* broken list */
		}
		curr = curr->nextNode;
		i++;
	} while(curr != part->tail);
	return i;
}

/* assumes list size is greater than 1 */
Boolean moveToHead(AddressBookNode * toMove, Part * part) {
	/* stitch up toMove */
	if(toMove->nextNode == NULL) {
		/* at tail */
		toMove->previousNode->nextNode = NULL;
	} else if(toMove->previousNode == NULL) {
		/* at head */
		toMove->nextNode->previousNode = NULL;
	} else {
		/* normal */
		toMove->previousNode->nextNode = toMove->nextNode;
		toMove->nextNode->previousNode = toMove->previousNode;
	}
	/* move toMove into head pos */
	toMove->nextNode = part->head;
	toMove->previousNode = part->head->previousNode;
	/* stitch up head */
	if(part->head->previousNode != NULL)/* not at list head */
		part->head->previousNode->nextNode = toMove;
	part->head->previousNode = toMove;
	part->head = toMove;
	return TRUE;
}

Boolean moveBefore(AddressBookNode * pos, AddressBookNode * toMove, Part * part) {
	/*printf("putting %s before %s\t", toMove->name, pos->name);
	printf("\t%s was before %s\t\n", toMove->previousNode->name, toMove->name);*/

	/* check part edge cases */
	if(part->head == toMove) {
		printf("you shouldn't be moving part head before something\n");
		part->head = toMove->nextNode;
	}
	if(part->tail == toMove) {
		/*printf("tomove %s is tail\tnew tail: %s \n", toMove->name, toMove->previousNode->name);*/
		part->tail = toMove->previousNode;
	} else {
		/*printf("part tail: %s\ttoMove: %s\n", part->tail->name,
		 * toMove->name);*/
	}
	if(part->head == pos) {
		part->head = toMove;
	}
	if(part->tail == pos) {
		/* nothing happens */
	}

	/* stitch up toMove */
	if(toMove->nextNode == NULL) {
		/* at tail */
		toMove->previousNode->nextNode = NULL;
	} else if(toMove->previousNode == NULL) {
		/* at head */
		/*part->head = toMove->nextNode;*//* make head work */
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
		pos->previousNode = toMove;
	} else {
		/* in middle */
		pos->previousNode->nextNode = toMove;
		pos->previousNode = toMove;
	}

	return TRUE;
}

/** get distance between 2 nodes
 * this assumes nodea comes before nodeb */
int nodeDiff(AddressBookNode * nodea, AddressBookNode * nodeb) {
	int i = 0;

	/*printf("\nfrom %s to %s\n", nodeb->name, nodea->name);*/
	while(nodeb != nodea) {
		if(nodeb == NULL) {
			printf("\n\t\tERROR: nodediff got to NULL (list head) before finding nodeA\t%d\n", i);
			return -1;
		}
		/*printf("%s\t", nodeb->name);*/
		nodeb = nodeb->previousNode;
		i++;
		if(i > 600) {
			printf("\t\tERROR: nodediff looped too many times");
			return -1;
		}
	}

	return i;
}

void fixlist(AddressBookList * list) {
	/* printf("fixing head\n");*/
	/* go to head */
	while(list->head->previousNode != NULL) {
		list->head = list->head->previousNode;
	}
	/*printf("fixing tail\n");*/
	/* go to tail */
	while(list->tail->nextNode != NULL) {
		list->tail = list->tail->nextNode;
	}
	/*printf("list... fixed?\n");*/
}

char* partStr(Part * part) {
	int size;
	char *str;
	char *substr;
	Boolean free_substr = FALSE;

	size = nodeDiff(part->head, part->tail);
	str = malloc(sizeof(*str) * (size+1));

	if(size <= 2) {
		substr = "";
	} else {
		substr = charLine('-', size-2);
		free_substr = TRUE;
	}

	if(size < 1) {
		sprintf(str, "%s", "");
	} else if(size == 1) {
		sprintf(str, "|");
	} else {
		sprintf(str, "|%s|", substr);
	}

	/*printf("\tPART: size: %d\t%s\n", size, str);*/
	
	if(free_substr)
		free(substr);

	return str;
}

void printParts(Part * parts, int partsize, AddressBookList * list) {
	int i;
	char *str = NULL;
	char *partstr;
	int start = 1;

	for(i = 0; i < partsize; i++) {
		partstr = partStr(&parts[i]);
		str = realloc(str, sizeof(*str) * (strlen(partstr) + (str == NULL ? 0 : strlen(str)) + 1));
		if(start) {
			start = 0;
			sprintf(str, "%s", partstr);
		} else {
			sprintf(str, "%s%s", str, partstr);
		}
		free(partstr);
	}

	printf("%s\n", str);

	free(str);
}

AddressBookNode * getPivot(Part * part) {
	int diff = nodeDiff(part->head, part->tail)/2;
	AddressBookNode * node = part->tail;
	printf("getting pivot\n");

	for(; diff >= 0; diff--) {
		printf("diff: %d\n", diff);
		node = node->previousNode;
	}
	return node;
}

/* queeeeek sort */
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
	AddressBookNode * tempnode;
	int sortInt;
	int diffa;
	int diffb;

	if(list->size == 0) {
		printf("no elements to sort\n");
		return;
	} else if(list->size == 1) {
		printf("can't sort a list of 1\n");
		return;
	}

	/* allocate first parition */
	parts = malloc(sizeof(*parts) * ++partsize);
	parts[0].head = list->head;
	parts[0].tail = list->tail;

	/* this doesn't preserve list->head and list->tail */
	/* god knows what it does to list->current */
	/* it actually just points to the same node it did before sorting */
	while(partsize > 0) {
		printParts(parts, partsize, list);
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
				nextnode = currnode->nextNode;
			}
			sortInt = sort(currnode, pivot);
			if(sortInt < 0) {
				/* currnode is less than pivot */
				if(!moveBefore(pivot, currnode, currpart))
					printf("\t\tERROR: can't move currnode before pivot\n");
			}
		} while(nextnode != NULL);

		/* redo parts */
		diffa = nodeDiff(currpart->head, pivot);
		diffb = nodeDiff(pivot, currpart->tail);

		if((diffa > 1) && (diffb > 1)) {
			/* grow array */
			/*printf("splitting parts %d\n", partsize);*/
			tempnode = currpart->tail;

			parts[partsize-1].head = currpart->head;
			parts[partsize-1].tail = pivot->previousNode;

			parts = realloc(parts, sizeof(*parts) * ++partsize);

			parts[partsize-1].head = pivot->nextNode;
			/* last part.tail = currpart->tail */
			parts[partsize-1].tail = tempnode;/* parts are being realloced so we need a temp var */
			/*printf("part %d: h-%s t-%s\n", partsize-2, parts[partsize-2].head->name, parts[partsize-2].tail->name);
			printf("part %d: h-%s t-%s\n", partsize-1, parts[partsize-1].head->name, parts[partsize-1].tail->name);*/
		} else if(diffa > 1) {
			/* array stays the same */
			/*printf("new, smaller part %d\n", partsize);*/
			parts[partsize-1].head = currpart->head;
			parts[partsize-1].tail = pivot->previousNode;
		} else if(diffb > 1) {
			/* array stays the same */
			/*printf("new, smaller part %d\n", partsize);*/
			parts[partsize-1].head = pivot->nextNode;
			parts[partsize-1].tail = currpart->tail;
		} else {
			/* shrink array */
			/*printf("eliminating last part %d\n", partsize);*/
			--partsize;
			if(partsize == 0)
				free(parts);
			else
				parts = realloc(parts, sizeof(*parts) * partsize);
		}
	}
	/* restore list->head and list->tail to their former glory */
	fixlist(list);
}

int compareNameR(const void * node, const void * otherNode) {
	return -1*compareName(node, otherNode);
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

int compareIDR(const void * node, const void * otherNode) {
	return -1*compareID(node, otherNode);
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

void commandSave(AddressBookList * list, char * fileName) {
	char* phones;
	FILE * file;
	AddressBookNode * node;
	
	if(list->size < 1) {
		printf("the list has no phone numbers to save\n");
		return;
	}
	/* open file */
	printf("opening the file: %s\n", fileName);
	file = fopen(fileName, "w");
	for(node = list->head; node != NULL; node = node->nextNode) {
		/* get phones in 1 string */
		phones = h_concatPhonesS(node->array, "%s,%s");
		/* write to file */
		if(strlen(phones) < TELEPHONE_LENGTH - NULL_SPACE)
			fprintf(file, "%d,%s\n", node->id, node->name);
		else
			fprintf(file, "%d,%s,%s\n", node->id, node->name, phones);
		/* free mallocs */
		free(phones);
	}
	/* close file */
	printf("closing the file\n");
	fclose(file);
}
