#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>
#include "huffman.c"
int main(int argc,char** argv){
    // if(argc<2){
    //     printf("Not enough paramters\n");
    // }
    huffman_encoder e;
    long long freqs[256]={0};
    freqs['A']=4;
    freqs['B']=7;
    freqs['C']=3;
    freqs['D']=2;
    freqs['E']=4;
    huffman_encoder_init(&e,freqs,256);
    for(int i=0;i<MAX_HUFFMAN_SYMBOLS;i++){
        if(e.lengts[i]){
            printf("%c-%lld-%lld\n",(char)i,e.lengts[i],e.codewords[i]);
        }
    }
    return 0;
}
