#include "addressbook.h"

/**
* This file is to contain the main menu loop and thus it will have console
* output, meaning printf's are expected to be seen in this file.
* 
* After the user enters a command, then the corresponding function is to be
* called from commands.c, e.g., "forward" corresponds to "commandForward(...)".
* test
*/
#include <stdio.h>
#define BUFFER_SIZE 200
#define STR_LEN 200
#define DELIM " "

void showStudentInformation() {
	char* name = "Student Name: Angel English";
	char* number = "Student Number: 3543536";
	char* apt = "Advanced Programming Techniques, "
				"Assignment 2, Semester 1 2017";
	char* line = charLine('-', strlen(apt));
	printf("%s\n", line);
	printf("%s\n", name);
	printf("%s\n", number);
	printf("%s\n", apt);
	printf("%s\n", line);
	free(line);
}

void printSize(AddressBookArray * arr, int i) {
	printf("size: %d\n", (int)sizeof(arr->telephones[i]));
}

int main(int argc, char ** argv)
{
	AddressBookList *list = NULL;

	
	menu();

	return 1;
	list = createAddressBookList();
	commandLoad("sml.txt", list);

	if(list == NULL)
		return EXIT_FAILURE;

	commandDisplay(list);
	/*printf("\nFREEING\n");*/

	/*commandSort(list, compareName);
	commandDisplay(list);
	commandSort(list, compareID);
	commandDisplay(list);*/
	
	commandUnload(list);
	commandDisplay(list);

	freeAddressBookList(list);


    return EXIT_SUCCESS;
}

void printHelp() {
	printf("available commands:\nhelp\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
			COMMAND_LOAD,
			COMMAND_UNLOAD,
			COMMAND_DISPLAY,
			COMMAND_SORT,
			COMMAND_FORWARD,
			COMMAND_BACKWARD,
			COMMAND_DELETE,
			COMMAND_QUIT
			);
}

/* removes toRemove from str, shortens str */
Boolean str_rem(char* str, char* toRemove) {
	int strtIdx;
	int endIdx;
	/*printf("removing '%s' from '%s'\n", toRemove, str);*/

	for(strtIdx = 0; ; strtIdx++) {
		if(strncmp(str + strtIdx, toRemove, (int)strlen(toRemove)) == 0)
			break;
	}
	endIdx = strtIdx + strlen(toRemove);

	if((strtIdx >= (int)strlen(str))) {
		printf("cannot find '%s'\n", toRemove);
		return FALSE;
	}

	while(str[endIdx] != '\0') {
		str[strtIdx++] = str[endIdx++];
	}
	str[strtIdx] = '\0';

	/*printf("str now: '%s'\n", str);*/
	return TRUE;
}

void menu() {
	char ** tokens;
	char str[STR_LEN];
	char str_bak[STR_LEN];
	AddressBookList *list;
	int (*compare)(const void*, const void*);
	char *endptr;
	int moves;
	int i;


/* NOT YET IMPLEMENTED
#define COMMAND_INSERT "insert"
#define COMMAND_ADD "add"
#define COMMAND_FIND "find"
#define COMMAND_DELETE "delete"
#define COMMAND_REMOVE "remove"
#define COMMAND_SAVE "save"
*/

	showStudentInformation();
	/*printf("Available Commands:\nload\nunload\ndisplay\nsort\nquit\nforward\nbackward\n");*/
	printHelp();

	list = createAddressBookList();
	while(TRUE) {

		if(getStr(str, STR_LEN)) {
			strcpy(str_bak, str);

			/* tokens is the address of the first position */
			tokens = h_token(str, DELIM);

			/*load*/	
			if(strcmp(COMMAND_LOAD, tokens[0]) == 0) {
				commandLoad(tokens[1], list);

			/* unload */
			} else if(strcmp(COMMAND_UNLOAD, tokens[0]) == 0) {
				commandUnload(list);

			/* display */
			} else if(strcmp(COMMAND_DISPLAY, tokens[0]) == 0) {
				commandDisplay(list);

			/* sort */
			} else if(strcmp(COMMAND_SORT, tokens[0]) == 0) {
				compare = NULL;
				/* check tokens1 is there */
				if(tokens[1] != NULL) {
					/* check what command it is */
					if(strcmp(COMMAND_SORT_NAME, tokens[1]) == 0) {
						compare = compareName;
					} else if(strcmp(COMMAND_SORT_ID, tokens[1]) == 0) {
						compare = compareID;
					} else {
						printf("invalid sort condition. valid ones are:\nname\nid\n");
					}
				} else {
					printf("invalid sort condition. valid ones are:\nname\nid\n");
				}

				if(compare != NULL)
					commandSort(list, compare);

			/* forward */
			} else if(strcmp(COMMAND_FORWARD, tokens[0]) == 0) {
				if(tokens[1] != NULL) {
					moves = strtol(tokens[1], &endptr, 10);
					if(endptr != NULL) {
						commandForward(list, moves-1);
					}
				}
				commandForward(list, 1);

			/* backward */
			} else if(strcmp(COMMAND_BACKWARD, tokens[0]) == 0) {
				if(tokens[1] != NULL) {
					moves = strtol(tokens[1], &endptr, 10);
					if(endptr != NULL) {
						commandBackward(list, moves-1);
					}
				}
				commandBackward(list, 1);
			/* insert */
			} else if(strcmp(COMMAND_INSERT, tokens[0]) == 0) {
				/* remove 'insert ' word */
				str_rem(str_bak, "insert ");
				/* token by comma */
				free(tokens);
				tokens = h_token(str_bak, ",");
				/* create node with data */
				for(i = 0; tokens[i] != NULL; i++)
					printf("%s\n", tokens[i]);
			/* delete */
			} else if(strcmp(COMMAND_DELETE, tokens[0]) == 0) {
				commandDelete(list);
			/* quit */
			} else if(strcmp(COMMAND_QUIT, tokens[0]) == 0) {
				free(tokens);
				break;
			} else if(strcmp("help", tokens[0]) == 0) {
				printHelp();
			/*not a command*/
			} else {
				printf("Invalid Input\n");
				printHelp();
			}
			free(tokens);
		}
	}
	freeAddressBookList(list);
}
















