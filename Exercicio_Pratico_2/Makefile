CC=g++
CFLAGS=-Wall -g -pg
LDFLAGS=-pg

programa: main.o
	$(CC) $(LDFLAGS) -o programa main.o

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

run: programa
	./programa $(METHOD) $(N)
	gprof programa gmon.out > relatorio.txt

clean:
	rm -f programa *.o *~ relatorio.txt
