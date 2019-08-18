#include <iostream>
#include <vector>
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
        print(root->l) ;
        print(root->r) ;
    }
}

vector<treeNode*> ls ;
//遍历树
void travel(treeNode* root1, treeNode* root2) {
    if(root1 && root2) {
        if(root1->data == root2->data) {
            ls.push_back(root1)  ;          
        }
        travel(root1->l, root2) ;
        travel(root1->r, root2) ;
    }
}   

int flag = 1;
//验证树是否相同
void verify(treeNode* root2, treeNode* partTree) {
    if(root2 && partTree && flag != 0) {
        if(root2->data != partTree->data)  {
            flag = 0 ;
            return ;
        }      
    }
}

void getRes(treeNode* root1, treeNode* root2) {
    //在树１中找和ｒｏｏｔ２相同根节点的树
    travel(root1, root2) ;
    int len = ls.size();
    cout << ls.size() << endl ;
    for(int i=0; i<len; i++) {
        verify(root2, ls[i]) ;
        if(flag == 1) {
            cout << "YES" << endl ;
            break ;
        }
    }
    if(flag == 0) {
        cout << "NO" << endl ;
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
    treeNode* root1 = NULL;
    treeNode* root2 = NULL;
    root1 = (treeNode*)malloc(sizeof(treeNode)) ;
    root2 = (treeNode*)malloc(sizeof(treeNode)) ;
    build(root1) ;
    build(root2) ;
    //判断树２是否为树１的子树
    getRes(root1, root2) ;
    destroyTree(root1) ;
    destroyTree(root2) ;
}   

