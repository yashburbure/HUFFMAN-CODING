compile:decode.o unzip.o
	gcc decode.o unzip.o -o decode
decode.o:decode.c 
	gcc decode.c -c 
unzip.o:unzip.c unzip.h
	gcc unzip.c -c