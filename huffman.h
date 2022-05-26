#ifndef HUFFMAN_H
#define HUFFMAN_H
#define MAX_HUFFMAN_SYMBOLS 260


typedef struct Hnode{
    char symbol;
    long long freq;
    struct Hnode* left;
    struct Hnode* right;
}Hnode;

typedef struct huffman_encoder{
    long long codewords[MAX_HUFFMAN_SYMBOLS];
    long long lengts[MAX_HUFFMAN_SYMBOLS];
}huffman_encoder;

Hnode* new_Hnode(char ch,long long freq);
// void build_huffman_trees(huffman_encoder* e,long long freqs[],long long n);
void huffman_encoder_init(huffman_encoder* e,long long freqs[],long long n);
#endif