#include"huffman.c"
#include"zip.h"
// #include"LZSS.c"
#ifndef ZIP_C
#define ZIP_C

FILE* table_writer(FILE* output,huffman_encoder e){
    int sum=0;
    for(int i=0;i<FREQ_SIZE;i++){
        if(e.lengts[i]!=0){
            sum++;
        }
    }
    fprintf(output,"%d",sum);
    for(int i=0;i<FREQ_SIZE;i++){
        if(e.lengts[i]){
            unsigned char ch=i;
            fprintf(output,"%c",i);
            fprintf(output,"%c",e.lengts[i]);
            fprintf(output,"%c",e.codewords[i]);
        }
    }
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
    FILE* output=fopen("output.hzip","w");
    output=table_writer(output,e);
    unsigned char ch;
    unsigned char buffer=0;
    int current_bit=0;
    while(fscanf(inpt,"%c",&ch)!=EOF){
        int code=e.codewords[(int)ch];
        int sz=e.lengts[(int)ch];
        for(int i=0;i<sz;i++){
            if(code&(1ll<<i)){
                buffer|=(1<<current_bit);
            }
            current_bit++;
            if(current_bit>7){
                fprintf(output,"%c",buffer);
                buffer=0;
                current_bit=0;
            }
        }
    }
    if(current_bit!=7) fprintf(output,"%c",buffer);
    fclose(inpt);
    fclose(output);
}
void zip(char* filename){
    // printf("ZIP Started\n");
    int* freqs=(int*)malloc(sizeof(int)*FREQ_SIZE);
    // printf("ZIP Started done\n");
    for(int i=0;i<FREQ_SIZE;i++){
        freqs[i]=0;
    }
    // printf("Freqency initilization done\n");
    count_frequency(filename,freqs);
    // printf("Frequency couting done\n");
    huffman_encoder e;
    huffman_encoder_init(&e,freqs,FREQ_SIZE);
    // printf("HUFFMAN Tree generated\n");
    create_file(filename,e);
}


#endif