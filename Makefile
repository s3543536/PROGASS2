SOURCES=addressbook.c addressbook_list.c addressbook_array.c commands.c helpers.c
OBJECTS=addressbook.o addressbook_list.o addressbook_array.o commands.o helpers.o
HEADERS=addressbook.h addressbook_list.h addressbook_array.h commands.h helpers.h
PROGRAM=a.out
FLAGS=-ansi -pedantic -Wall -g

all: $(PROGRAM)
$(PROGRAM): $(OBJECTS)
	gcc $(FLAGS) -o $(PROGRAM) $(OBJECTS)

addressbook.o: addressbook.c $(HEADERS)
	gcc $(FLAGS) -c addressbook.c

addressbook_list.o: addressbook_list.c $(HEADERS)
	gcc $(FLAGS) -c addressbook_list.c

addressbook_array.o: addressbook_array.c $(HEADERS)
	gcc $(FLAGS) -c addressbook_array.c

commands.o: commands.c $(HEADERS)
	gcc $(FLAGS) -c commands.c

helpers.o: helpers.c $(HEADERS)
	gcc $(FLAGS) -c helpers.c

clean:
	rm $(PROGRAM) $(OBJECTS)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile

