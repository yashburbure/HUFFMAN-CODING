#ifndef HASHMAP_H
#define HASHMAP_H
#define MAP_SIZE 10000
#define ll unsigned long long 
typedef struct Hnode{
    ll code,size;
    char encodedChar;
    struct Hnode* next;
}Hnode;
typedef struct HashMap{
    Hnode* HashArr[MAP_SIZE];
}HashMap;

void initMap(HashMap* mp);
void insertMap(HashMap* mp,ll code,ll size,char ch);
int findMap(HashMap mp,ll code,ll size);
void printMap(HashMap mp);
#endif