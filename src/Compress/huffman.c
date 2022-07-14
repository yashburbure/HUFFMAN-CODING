#ifndef HUFFMAN_C
#define HUFFMAN_C

#include"huffman.h"
#include "heap.h"
#include<assert.h>
#include<stdlib.h>
#include<limits.h>

Hnode* new_Hnode(char ch,int freq){
    Hnode* nn=(Hnode*)malloc(sizeof(Hnode));
    nn->freq=freq;
    nn->symbol=ch;
    nn->left=nn->right=NULL;
    return nn;
}

void generate_code(Hnode* root,unsigned long long *curr_cw,int* bit,huffman_encoder* e){
    if(!root){
        return;
    }
    if(root->left || root->right){
        (*bit)++;
        generate_code(root->left,curr_cw,bit,e);
        (*bit)--;
        *curr_cw=(*curr_cw)|(1ll<<(*bit));
        (*bit)++;
        generate_code(root->right,curr_cw,bit,e);
        (*bit)--;
        *curr_cw=(*curr_cw)^(1ll<<(*bit));
    }
    else{
        e->codewords[root->symbol]=*curr_cw;
        e->lengts[root->symbol]=*bit;
        assert(*bit<=62 && "HUFFMAN code size too large");
    }
}

void compute_canonical_code(huffman_encoder* e,Hnode* root){
    for(int i=0;i<MAX_HUFFMAN_SYMBOLS;i++){
        e->codewords[i]=0ll;
        e->lengts[i]=0ll;
    }
    unsigned long long curr_codewords=0ll;
    int bit=0;
    generate_code(root,&curr_codewords,&bit,e);
}
Hnode* destroy_huffman_tree(Hnode* root){
    if(!root) return NULL;
    root->left=destroy_huffman_tree(root->left);
    root->right=destroy_huffman_tree(root->right);
    Hnode* del=root;
    free(del);
    return NULL;
}

void build_huffman_tree(huffman_encoder* e,int freqs[],int n){
    long long freq_sum=0;
    for(int i=0;i<n;i++){
        freq_sum+=freqs[i];
    }
    assert(freq_sum<=INT_MAX && "File size too large!");
    heap h;
    init_heap(&h);
    for(int i=0;i<n;i++){
        if(freqs[i]){
            Hnode* nn=new_Hnode((char)i,freqs[i]);
            push_heap(&h,nn);
        }
    }
    if(size_heap(h)==1){
        Hnode* front=top_heap(h);
        e->codewords[front->symbol]=0;
        e->lengts[front->symbol]=1;
        free_heap(&h);
        return;
    }
    Hnode* root=NULL;
    while(size_heap(h)>1){
        Hnode* front1=top_heap(h);
        pop_heap(&h);
        Hnode* front2=top_heap(h);
        pop_heap(&h);
        Hnode* nn=new_Hnode('-',front1->freq+front2->freq);
        push_heap(&h,nn);
        nn->left=front1;
        nn->right=front2;   
    }
    root=top_heap(h);
    compute_canonical_code(e,root);
    root=destroy_huffman_tree(root);
    free_heap(&h);
}
void huffman_encoder_init(huffman_encoder* e,int freqs[],int n){
    for(int i=0;i<MAX_HUFFMAN_SYMBOLS;i++){
        e->codewords[i]=0ll;
        e->lengts[i]=0ll;
    }
    build_huffman_tree(e,freqs,n);
}

#endif