CC=gcc
CFLAGS=-c -Wall -std=c11

all: qtest

qtest: qtest.o sqrlib.o
	$(CC) qtest.o sqrlib.o -o qtest
	make clean
qtest.o: qtest.c
	$(CC) $(CFLAGS) qtest.c
sqrlib.o: sqrlib.c
	$(CC) $(CFLAGS) sqrlib.c
test: 
	./qtest
clean:
	rm -rf *.o
