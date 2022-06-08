#ifndef UNZIP_C
#define UNZIP_C
#define FREQ_SIZE 256
//char ,length,codeword
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
    // printf("%d\n",no_ele);
    for(int i=0;i<no_ele;i++){
        char ch;
        fscanf(file,"%c",&ch);
        int index=(int)ch;
        fscanf(file,"%c",&ch);
        lengths[index]=(int)ch;
        fscanf(file,"%c",&ch);
        codewords[index]=(int)ch;
        // printf("%c %d %d \n",index,lengths[index],codewords[index]);
    }
    return file;
}
void unzip(char* filename){
    FILE* file=fopen(filename,"r");
    if(!file){
        printf("Can't Open file\n");
        return;
    }
    FILE* out=fopen("out.txt","w");
    int codewords[FREQ_SIZE]={0};
    int lengths[FREQ_SIZE]={0};
    file=table_reader(file,codewords,lengths);
    unsigned char ch;
    unsigned int buffer=0;
    int buffer_size=0;
    while(fscanf(file,"%c",&ch)!=EOF){
        for(int i=7;i>=0;i--){
            if(ch&(1<<i)){
                buffer|=(1<<buffer_size);
            }
            buffer_size++;
            for(int i=0;i<FREQ_SIZE;i++){
                if(codewords[i]==buffer && lengths[i]==buffer_size){
                    fprintf(out,"%c",i);
                    // printf("%d ",i);
                    buffer=0;
                    buffer_size=0;
                    break;  
                }
            }
        }
    }
}


#endif