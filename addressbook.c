#include "addressbook.h"

/**
* This file is to contain the main menu loop and thus it will have console
* output, meaning printf's are expected to be seen in this file.
* 
* After the user enters a command, then the corresponding function is to be
* called from commands.c, e.g., "forward" corresponds to "commandForward(...)".
*/
#include <stdio.h>
#define BUFFER_SIZE 200

/**
 * returns the contents of the file 'fname'
 */
char* loadFileText(char* fname) {
	FILE *file;
	char buffer[BUFFER_SIZE];
	char *fileText = NULL;/* realloc needs NULL so it knows to assign new memory*/
	unsigned int size = 0;

	file = fopen(fname, "r");
	while(fgets(buffer, sizeof(char) * BUFFER_SIZE, file)) {
		/*printf("buffer: %s", buffer);*/
		size++;
		fileText = realloc(fileText, (size_t)(BUFFER_SIZE * size));
		strcat(fileText, buffer);

	}
	fclose(file);
	return fileText;
}

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

int main(int argc, char ** argv)
{
	FILE *file;
	char buffer[BUFFER_SIZE];

	file = fopen("sml.txt", "r");
	while(fgets(buffer, BUFFER_SIZE, file)) {
		printf("buffer: %s", buffer);
	}
	fclose(file);


	showStudentInformation();
	printf("%s\n", loadFileText("sml.txt"));
    printf("> Goodbye. \n\n");

    return EXIT_SUCCESS;
}
