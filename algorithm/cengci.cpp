#include <iostream>
#include <stdio.h>
#include <queue>
#include <stdlib.h>

using namespace std ;
typedef struct tree {
    struct tree* l, *r ;
    int a ;
} treeNode;

void build(treeNode* root){
    cin >> root->a;
    if(root->a == -1) {
        free(root) ;
        root = NULL ;
        return ;
    }
    root->l = (treeNode*)malloc(sizeof(treeNode)) ;
    build(root->l) ;
    root->r = (treeNode*)malloc(sizeof(treeNode)) ;
    build(root->r) ;
}

void print(treeNode* root) {
    if(root) {
        print(root->l) ;
        print(root->r) ;
        cout <<root->a << endl ;
    }
}

void destroy(treeNode* root){
    if(root) {
        destroy(root->l) ;
        destroy(root->r) ;
        if(!root) {
            free(root) ;
        }
    }   
}

void cengci(treeNode*root) {
    queue<treeNode*>q ;
    if(root != NULL)
    q.push(root) ;
    while(!q.empty()) {
        treeNode* tmp = q.front() ;
        cout << tmp->a << endl ;
        q.pop() ;
        if(tmp->l != NULL)
        q.push(tmp->l) ;
        if(tmp->r != NULL)
        q.push(tmp->r) ;
    }
}

int main() {
    treeNode* root = NULL;
    root = (treeNode*)malloc(sizeof(treeNode)) ;
    build(root) ;  
    print(root) ;       
    cengci(root) ;
    destroy(root) ;
    return 0;
}

