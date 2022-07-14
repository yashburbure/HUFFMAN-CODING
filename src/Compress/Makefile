compile:main.o compress.o decompress.o huffman.o heap.o
	gcc main.o compress.o decompress.o huffman.o heap.o -o main
main.o:main.c
	gcc main.c -c
compress.o:compress.c compress.h
	gcc compress.c -c
decompress.o:decompress.c decompress.h
	gcc decompress.c -c
huffman.o:huffman.c huffman.h
	gcc huffman.c -c
heap.o:heap.c heap.h
	gcc heap.c -c