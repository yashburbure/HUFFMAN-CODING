#ifndef UNZIP_C
#define UNZIP_C
#define FREQ_SIZE 256


FILE* table_reader(FILE* file,int codewords[],int lengths[]){
    unsigned int no_ele=0;
    int index=31;
    unsigned char ch;
    for(int i=0;i<4;i++){
        fscanf(file,"%c",&ch);
        for(int j=7;j>=0;j--){
            if(ch&(1<<j)) no_ele|=(1<<index);
            index--;
        }
    }
    for(int i=0;i<no_ele;i++){
        char ch;
        fscanf(file,"%c",&ch);
        int index=(int)ch;
        fscanf(file,"%c",&ch);
        lengths[index]=(int)ch;
        fscanf(file,"%c",&ch);
        codewords[index]=(int)ch;
    }
    return file;
}
void unzip(char* filename){
    FILE* file=fopen(filename,"rb");
    if(!file){
        printf("Can't Open file\n");
        return;
    }
    FILE* out=fopen("out.txt","w");
    int codewords[FREQ_SIZE]={0};
    int lengths[FREQ_SIZE]={0};
    file=table_reader(file,codewords,lengths);
    int bitswritten;
    fread(&bitswritten,sizeof(bitswritten),1,file);
    unsigned char ch;
    unsigned int buffer=0;
    int buffer_size=0;
    int bitsread=0;
    while(fread(&ch,sizeof(ch),1,file)){
        for(int i=7;i>=0;i--){
            bitsread++;
            if(ch&(1<<i)){
                buffer|=(1<<buffer_size);
            }
            buffer_size++;
            for(int i=0;i<FREQ_SIZE;i++){
                if(codewords[i]==buffer && lengths[i]==buffer_size){
                    fprintf(out,"%c",i);
                    buffer=0;
                    buffer_size=0;
                    break;  
                }
            }
            if(bitsread==bitswritten){
                return;
            }
        }
    }
}


#endif