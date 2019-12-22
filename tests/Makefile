CC=gcc
CFLAGS=-c -Wall
SDIR=../src

all: stack_test queue_test ring_test

stack_test: stack_test.o sqrlib.o
	$(CC) stack_test.o sqrlib.o -o stack_test

stack_test.o: stack_test.c
	$(CC) $(CFLAGS) stack_test.c
	
queue_test: queue_test.o sqrlib.o
	$(CC) queue_test.o sqrlib.o -o queue_test

queue_test.o: queue_test.c
	$(CC) $(CFLAGS) queue_test.c

ring_test: ring_test.o sqrlib.o
	$(CC) ring_test.o sqrlib.o -o ring_test

ring_test.o: ring_test.c
	$(CC) $(CFLAGS) ring_test.c
	
sqrlib.o: $(SDIR)/sqrlib.c
	$(CC) $(CFLAGS) $(SDIR)/sqrlib.c

test: 
	./stack_test
	./queue_test
	./ring_test
	
clean:
	rm -rf *.o
