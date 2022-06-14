#include"huffman.c"
#include"zip.h"
#ifndef ZIP_C
#define ZIP_C

int count_noofbits_written(char* filename,huffman_encoder e){
    int bitswritten=0;
    FILE* inpt=fopen(filename,"r");
    unsigned char ch;
    while(fscanf(inpt,"%c",&ch)!=EOF){
        int code=e.codewords[(int)ch];
        int sz=e.lengts[(int)ch];
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
    unsigned char ch;
    int index=31;
    for(int i=0;i<4;i++){
        unsigned char ch=0;
        for(int j=7;j>=0;j--){
            if(sum&(1<<index)){
                ch=ch|(1<<j);
            }
            index--;
        }
        fwrite(&ch,sizeof(ch),1,output);
    }
    for(int i=0;i<FREQ_SIZE;i++){
        if(e.lengts[i]){
            unsigned char ch=i;
            fwrite(&ch,sizeof(ch),1,output);
            ch=e.lengts[i];
            fwrite(&ch,sizeof(ch),1,output);
            ch=e.codewords[i];
            fwrite(&ch,sizeof(ch),1,output);
        }
    }
    int bitswritten=count_noofbits_written(filename,e);
    fwrite(&bitswritten,sizeof(bitswritten),1,output);
    return output;
}

void count_frequency(char* filename,int* freqs){
    FILE* file=fopen(filename,"r");
    assert(file!=NULL && "Can't open file");
    unsigned char ch;
    while(fscanf(file,"%c",&ch)!=EOF){
        freqs[(int)ch]++;
    }
    fclose(file);
}
void create_file(char* filename,huffman_encoder e){
    FILE* inpt=fopen(filename,"r");
    FILE* output=fopen("output.hzip","wb");
    output=table_writer(filename,output,e);
    unsigned char ch;
    unsigned char buffer=0;
    int current_bit=7;
    while(fscanf(inpt,"%c",&ch)!=EOF){
        int code=e.codewords[(int)ch];
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
void zip(char* filename){
    int* freqs=(int*)malloc(sizeof(int)*FREQ_SIZE);
    for(int i=0;i<FREQ_SIZE;i++){
        freqs[i]=0;
    }
    count_frequency(filename,freqs);
    huffman_encoder e;
    huffman_encoder_init(&e,freqs,FREQ_SIZE);
    create_file(filename,e);
}


#endif