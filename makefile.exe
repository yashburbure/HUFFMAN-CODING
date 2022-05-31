output:main.o zip.o huffman.o heap.o
	gcc main.o zip.o huffman.o heap.o -o main
main.o:main.c
	gcc -c main.c
zip.o:zip.c zip.h
	gcc -c zip.c
huffman.o:huffman.c huffman.h 
	gcc -c huffman.c 
heap.o:heap.c heap.h
	gcc -c heap.c
clean:
	rm *.o