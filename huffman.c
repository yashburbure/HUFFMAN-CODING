#include"huffman.h"
#include "heap.c"

#ifndef HUFFMAN_C
#define HUFFMAN_C
Hnode* new_Hnode(char ch,long long freq){
    Hnode* nn=(Hnode*)malloc(sizeof(Hnode));
    nn->freq=freq;
    nn->symbol=ch;
    nn->left=nn->right=NULL;
    return nn;
}

void generate_code(Hnode* root,long long *curr_cw,long long* bit,huffman_encoder* e){
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
    }
}

void compute_canonical_code(huffman_encoder* e,Hnode* root){
    for(int i=0;i<MAX_HUFFMAN_SYMBOLS;i++){
        e->codewords[i]=0;
        e->lengts[i]=0;
    }
    long long curr_codewords=0;
    long long bit=0;
    generate_code(root,&curr_codewords,&bit,e);
}

// void preorder(Hnode* root,int *i,char str[]){
//     if(!root) return;
//     if(root->left || root->right){
//         str[*i]='0';
//         (*i)++;
//         preorder(root->left,i,str);
//         (*i)--;
//         str[*i]='1';
//         (*i)++;
//         preorder(root->right,i,str);
//         (*i)--;
//         str[*i]='\0';
//     }
//     else{
//         printf("%c-%s-%d\n",root->symbol,str,root->freq);
//     }
// }
void build_huffman_tree(huffman_encoder* e,long long freqs[],long long n){
    long long freq_sum=0;
    for(int i=0;i<n;i++){
        freq_sum+=freqs[i];
    }
    assert(freq_sum<=INT_MAX && "Frequency Sum too large!");
    heap h;
    init_heap(&h);
    for(int i=0;i<n;i++){
        if(freqs[i]){
            Hnode* nn=new_Hnode((char)i,freqs[i]);
            push_heap(&h,nn);
        }
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
    // char str[100];
    // str[0]='\0';
    // int i=0;
    // preorder(root,&i,str);
}


void huffman_encoder_init(huffman_encoder* e,long long freqs[],long long n){
    build_huffman_tree(e,freqs,n);
}

#endif