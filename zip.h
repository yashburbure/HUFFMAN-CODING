#ifndef ZIP_H
#define ZIP_H

#define FREQ_SIZE 256

FILE* table_writer(char* filename,FILE* output,huffman_encoder e);
void create_file(char* filename,huffman_encoder e);
void count_frequency(char* filename,int* freqs);
void zip(char *filename);


#endif