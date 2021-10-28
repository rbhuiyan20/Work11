all: work11.o
	gcc -o output work11.o

work11.o: work11.c
	gcc -c work11.c

run:
	./output

clean:
	rm *.o
	rm output
	rm *.txt

