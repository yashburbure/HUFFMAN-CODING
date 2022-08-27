compile:main.o compress.o decompress.o hashMap.o huffman.o heap.o
	gcc main.o compress.o decompress.o hashMap.o huffman.o heap.o -o main
main.o:main.c
	gcc main.c -c
compress.o:compress.c compress.h
	gcc compress.c -c
decompress.o:decompress.c decompress.h
	gcc decompress.c -c
hashMap.o:hashMap.c hashMap.h
	gcc hashMap.c -c
huffman.o:huffman.c huffman.h
	gcc huffman.c -c
heap.o:heap.c heap.h
	gcc heap.c -c
removeo: *.o
	rm *.o