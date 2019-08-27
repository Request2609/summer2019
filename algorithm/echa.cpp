#include <iostream>
#include <stdlib.h>
using namespace std ;
typedef struct tree {
    int data ;
    struct tree* r ;
    struct tree* l ;
} treeNode;

//创建一个二茬树
void build(treeNode* root) {
    cin >> root->data ;
    if(root->data == -1) {
        free(root) ;
        root = NULL ;
        return ;
    }
    root->l = (treeNode*)malloc(sizeof(treeNode)) ;
    build(root->l) ; 
    root->r = (treeNode*)malloc(sizeof(treeNode)) ;
    build(root->r) ;
}

//先序创建一颗二叉树
void print(treeNode* root) {
    if(root) {
        cout << root->data << endl ;
        print(root->l) ;
        print(root->r) ;
    }
}

void destroyTree(treeNode* root) {
    if(root) {
        destroyTree(root->l) ;
        destroyTree(root->r) ;
        if(!root)
        free(root) ;
    }   
}

int main() {
    treeNode* root = NULL ;
    root = (treeNode*)malloc(sizeof(treeNode)) ;
    build(root) ;
    print(root) ;
}
