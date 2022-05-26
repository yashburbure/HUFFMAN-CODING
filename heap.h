#include"huffman.h"
#ifndef HEAP_H
#define HEAP_H

typedef struct heap{
    Hnode** A;
    int size;
    int top;
}heap;
void init_heap(heap* h);
int is_empty(heap h);
void push_heap(heap* h,Hnode* ele);
Hnode* top_heap(heap h);
void pop_heap(heap* h);
int size_heap(heap h);
void free_heap(heap *h);
#endif