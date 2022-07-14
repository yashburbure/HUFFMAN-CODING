#include<stdio.h>
int main(int argc,char** argv){
    if(argc<=2){
        printf("Not Enough Arguments\n");
        return 0;
    }
    FILE* file1=fopen(argv[1],"r");
    FILE* file2=fopen(argv[2],"r");
    if(!file1 || !file2){
        printf("File not opening\n");
        return 0;
    }
    unsigned char ch1,ch2;
    while(fscanf(file1,"%c",&ch1)!=EOF && fscanf(file2,"%c",&ch2)){
        if(ch1!=ch2){
            printf("Files are not identical\n");
            return 0;
        }
    }
    if(fscanf(file1,"%c",&ch1)==fscanf(file2,"%c",&ch2)){
        printf("Files are identical\n");
    }
    else{
        printf("Files are not identical\n");
    }
    return 0;
}