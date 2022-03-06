CC = clang

CFLAGS = -g

#STRICT FLAGS
#CFLAGS = -g -Wall -Wpedantic -Werror -Wextra
all: businessdb

businessdb: hashtable.o businessdb.o
	$(CC) businessdb.o  hashtable.o -o businessdb

hashtable.o:
	$(CC) $(CFLAGS) -c hashtable.c

businessdb.o:
	$(CC) $(CFLAGS) -c businessdb.c

clean:
	rm -f businessdb.o hashtable.o businessdb

format:
	clang-format -i -style=file *.[ch]
