#ifndef COMPRESS_C
#define COMPRESS_C

#include"./huffman.h"
#include"compress.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int count_noofbits_written(char* filename,huffman_encoder e){
    int bitswritten=0;
    FILE* inpt=fopen(filename,"r");
    unsigned char ch;
    while(fscanf(inpt,"%c",&ch)!=EOF){
        int sz=(int)e.lengts[(int)ch];
        bitswritten+=sz;
    }
    fclose(inpt);
    return bitswritten;
}
FILE* table_writer(char* filename,FILE* output,huffman_encoder e){
    unsigned int sum=0;
    for(int i=0;i<FREQ_SIZE;i++){
        if(e.lengts[i]!=0){
            sum++;
        }
    }
    fwrite(&sum,sizeof(sum),1,output);
    for(int i=0;i<FREQ_SIZE;i++){
        if(e.lengts[i]){
            unsigned char ch=i;
            fwrite(&ch,sizeof(ch),1,output);
            ch=e.lengts[i];
            fwrite(&ch,sizeof(ch),1,output);
            unsigned long long code=e.codewords[i];
            fwrite(&code,sizeof(code),1,output);
        }
    }
    int bitswritten=count_noofbits_written(filename,e);
    fwrite(&bitswritten,sizeof(bitswritten),1,output);
    return output;
}

int count_frequency(char* filename,int* freqs){
    FILE* file=fopen(filename,"r");
    if(!file){
        printf("Can't Open file\n");
        return 0;
    }
    assert(file!=NULL && "Can't open file");
    unsigned char ch;
    while(fscanf(file,"%c",&ch)!=EOF){
        freqs[(int)ch]++;
    }
    fclose(file);
    return 1;
}
void create_file(char* filename,huffman_encoder e){
    FILE* inpt=fopen(filename,"r");
    if(!inpt){
        printf("Can't Open file\n");
        return;
    }
    FILE* output=fopen("output.dat","wb");
    output=table_writer(filename,output,e);
    unsigned char ch;
    unsigned char buffer=0;
    int current_bit=7;
    while(fscanf(inpt,"%c",&ch)!=EOF){
        unsigned long long code=e.codewords[(int)ch];
        int sz=e.lengts[(int)ch];
        for(int i=0;i<sz;i++){
            if(code&(1ll<<i)){
                buffer|=(1<<current_bit);
            }
            current_bit--;
            if(current_bit<0){
                fwrite(&buffer,sizeof(buffer),1,output);
                buffer=0;
                current_bit=7;
            }
        }
    }
    if(current_bit!=7){
        fwrite(&buffer,sizeof(buffer),1,output);
    }
    fclose(inpt);
    fclose(output);
}
void compress(char* filename){
    int* freqs=(int*)malloc(sizeof(int)*FREQ_SIZE);
    for(int i=0;i<FREQ_SIZE;i++){
        freqs[i]=0;
    }
    if(!count_frequency(filename,freqs)){
        return ;
    }
    huffman_encoder e;
    huffman_encoder_init(&e,freqs,FREQ_SIZE);
    create_file(filename,e);
    printf("%s compressed to output.dat\n",filename);
}


#endif