#include<stdio.h>
#include "zip.h"
int main(int argc,char** argv){
    if(argc<2){
        printf("Not enough paramters\n");
        return 0;
    }
    zip(argv[1]);
    return 0;
}
