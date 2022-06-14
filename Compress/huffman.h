#ifndef HUFFMAN_H
#define HUFFMAN_H
#define MAX_HUFFMAN_SYMBOLS 256


typedef struct Hnode{
    unsigned char symbol;
    int freq;
    struct Hnode* left;
    struct Hnode* right;
}Hnode;

typedef struct huffman_encoder{
    int codewords[MAX_HUFFMAN_SYMBOLS];
    int lengts[MAX_HUFFMAN_SYMBOLS];
}huffman_encoder;

Hnode* new_Hnode(char ch,int freq);
void huffman_encoder_init(huffman_encoder* e,int freqs[],int n);
#endif