#include<stdio.h>
#include<stdlib.h>
#include"unzip.h"
int main(int argc,char** argv){
    if(argc<2){
        printf("Not enough parameters\n");
        return 0;
    }
    unzip(argv[1]);
    return 0;
}