#include"hashMap.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#ifndef HASHMAP_C
#define HASHMAP_C


Hnode* newHnode(ll code,ll size,char encodedChar){
    Hnode* nn=(Hnode*)malloc(sizeof(Hnode));
    nn->code=code;
    nn->size=size;
    nn->encodedChar=encodedChar;
    nn->next=NULL;
    return nn;
}
void initMap(HashMap* mp){
    for(int i=0;i<MAP_SIZE;i++){
        mp->HashArr[i]=NULL;
    }
}
int HashFunction(ll code,ll size){
    int HashValue=(code)%MAP_SIZE;
    HashValue=(HashValue+(size%MAP_SIZE))%MAP_SIZE;
    return HashValue;
}
void insertMap(HashMap *mp,ll code,ll size,char ch){
    int HashValue=HashFunction(code,size);
    if(mp->HashArr[HashValue]==NULL){
        mp->HashArr[HashValue]=newHnode(code,size,ch);
        return;
    }
    Hnode* head=mp->HashArr[HashValue];
    while(head){
        if(head->code==code && head->size==size){
            head->encodedChar=ch;
            return;
        }
        head=head->next;
    }
    Hnode* nn=newHnode(code,size,ch);
    nn->next=mp->HashArr[HashValue];
    mp->HashArr[HashValue]=nn;
}
int findMap(HashMap mp,ll code,ll size){
    int HashValue=HashFunction(code,size);
    Hnode* head=mp.HashArr[HashValue];
    while(head){
        if(head->code==code && head->size==size){
            return head->encodedChar;
        }
        head=head->next;
    }
    return INT_MIN;
}

#endif