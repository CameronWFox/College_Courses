INCLUDE_DIR=./include
OBJS_DIR=./objs

all: rng.o

rng.o: rng.c rng.h copyheader
	gcc -o rng.o -c -Wall rng.c -I $(INCLUDE_DIR)
	cp -f rng.o $(OBJS_DIR)	

copyheader:
	cp -f rng.h $(INCLUDE_DIR)
	
clean:
	rm -rf *~ *.o
