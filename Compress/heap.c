#ifndef HEAP_C
#define HEAP_C

#include"heap.h"
#include<stdlib.h>

static void swap(Hnode** A,int i,int j){
    Hnode* temp=A[i];
    A[i]=A[j];
    A[j]=temp;
}
void init_heap(heap* h){
    h->size=500;
    h->top=-1;
    h->A=(Hnode**)malloc(sizeof(Hnode*)*500);
}
int is_empty(heap h){
    return h.top==-1;
}
void push_heap(heap* h,Hnode* ele){
    h->A[++h->top]=ele;
    int ind=(h->top);
    int par=(ind-1)/2;
    while(par>=0 && h->A[ind]->freq<h->A[par]->freq){
        swap(h->A,ind,par);
        ind=par;
        par=(par-1)/2;
    }
}
Hnode* top_heap(heap h){
    return h.A[0];
}
void pop_heap(heap* h){
    if(h->top==-1) return;
    swap(h->A,0,h->top);
    h->top--;
    int ind=0;
    int l,r;
    while(ind<=h->top){
        l=(2*ind)+1;
        r=(2*ind)+2;
        if(l<=h->top){
            if(r<=h->top){
                int child=(h->A[l]->freq<h->A[r]->freq)?l:r;
                if(h->A[ind]->freq>h->A[child]->freq){
                    swap(h->A,ind,child);
                    ind=child;
                }
                else break;
            }
            else{
                int child=l;
                if(h->A[ind]->freq>h->A[child]->freq){
                    swap(h->A,ind,child);
                    ind=child;
                }
                else break;
            }
        }
        else return;
    }
}
int size_heap(heap h){
    return h.top+1;
}
void free_heap(heap* h){
    free(h->A);
}
#endif