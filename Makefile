SOURCES=addressbook.c addressbook_list.c addressbook_array.c commands.c helpers.c
OBJECTS=addressbook.o addressbook_list.o addressbook_array.o commands.o helpers.o
HEADERS=addressbook.h addressbook_list.h addressbook_array.h commands.h helpers.h
PROGRAM=a.out
FLAGS=-ansi -pedantic -Wall -g

all: $(PROGRAM)

%.o: %.c $(HEADERS)
	gcc $(FLAGS) -c $< -o $@

$(PROGRAM): $(OBJECTS)
	gcc -o $@ $^

.PHONY:clean archive

clean:
	rm $(PROGRAM) $(OBJECTS)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile

