compile:main.o zip.o huffman.o heap.o
	gcc main.o zip.o huffman.o heap.o -o encode
main.o:main.c
	gcc main.c -c
zip.o:zip.c zip.h 
	gcc zip.c -c 
huffman.o:huffman.c huffman.h
	gcc huffman.c -c 
heap.o:heap.c heap.h 
	gcc heap.c -c 