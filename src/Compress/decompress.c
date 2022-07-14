#ifndef DECOMPRESS_C
#define DECOMPRESS_C
#define FREQ_SIZE 256
#include<stdio.h>
#include"decompress.h"
FILE* table_reader(FILE* file,unsigned long long codewords[],unsigned long long lengths[]){
    unsigned int no_ele=0;
    fread(&no_ele,sizeof(no_ele),1,file);
    for(int i=0;i<no_ele;i++){
        unsigned char ch;
        fread(&ch,sizeof(ch),1,file);
        int index=(int)ch;
        fread(&ch,sizeof(ch),1,file);
        lengths[index]=(int)ch;
        unsigned long long code;
        fread(&code,sizeof(code),1,file);
        codewords[index]=code;
    }
    return file;
}
void decompress(char* filename){
    FILE* file=fopen(filename,"rb");
    if(!file){
        printf("Can't Open file\n");
        return;
    }
    FILE* out=fopen("out.txt","wb");
    if(!out){
        printf("Can't write in file\n");
        return;
    }
    unsigned long long codewords[FREQ_SIZE];
    unsigned long long lengths[FREQ_SIZE];
    for(int i=0;i<FREQ_SIZE;++i){
        codewords[i]=0ll;
        lengths[i]=0ll;
    }
    file=table_reader(file,codewords,lengths);
    int bitswritten;
    fread(&bitswritten,sizeof(bitswritten),1,file);
    unsigned char ch;
    unsigned long long buffer=0;
    unsigned long long buffer_size=0;
    int bitsread=0;
    while(fread(&ch,sizeof(ch),1,file)!=EOF){
        for(int i=7;i>=0;i--){
            bitsread++;
            if(ch&(1<<i)){
                buffer|=(1<<buffer_size);
            }
            buffer_size++;
            for(int i=0;i<FREQ_SIZE;i++){
                if(codewords[i]==buffer && lengths[i]==buffer_size){
                    fprintf(out,"%c",(char)i);
                    buffer=0;
                    buffer_size=0;
                    break;  
                }
            }
            if(bitsread==bitswritten){
                fclose(out);
                fclose(file);
                printf("%s decompressed to out.txt\n",filename);
                return;
            }
        }
    }
    fclose(out);
    fclose(file);
    printf("%s decompressed to out.txt\n",filename);
}


#endif