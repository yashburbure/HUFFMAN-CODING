#include<stdio.h>
#include<string.h>
#include"compress.h"
#include"decompress.h"  
int main(int argc,char** argv){
    while(1){
        int choice;
        printf("Enter 1 to Compress File\nEnter 2 to Decompress File\nEnter 3 to Exit\n");
        printf("Choice : ");
        scanf("%d",&choice);
        char ch;
        scanf("%c",&ch);
        if(choice==1){
            printf("Enter File Name: ");
            char filename[50];
            fgets(filename,50,stdin);
            for(int i=0;i<50;i++){
                if(filename[i]==' ' || filename[i]=='\n' || filename[i]=='\0'){
                    filename[i]='\0';
                    break;
                }
            }
            compress(filename);
            printf("\n");
        }
        else if(choice==2){
            printf("Enter File Name: ");
            char filename[50];
            fgets(filename,50,stdin);
            for(int i=0;i<50;i++){
                if(filename[i]==' ' || filename[i]=='\n' || filename[i]=='\0'){
                    filename[i]='\0';
                    break;
                }
            }
            decompress(filename);
            printf("\n");
        }
        else if(choice==3){
            return 0;
        }
        else{
            printf("Invalid choice\n");
        }
        fflush(stdin);
    }
    return 0;
}
