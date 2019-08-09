#include <iostream>
/*
 输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。 假设输入的前序遍历和中序遍历的结果都不含重复的数字。
 例如， 输入前序遍历序列 {1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}， 则重建出二叉树并输出它的头结点。
 * */
//重建二叉树
struct tree {
    int i ;
    tree* r, *l ;
} ;

//中序序列中找该节点下标
int findIndex(int pre, int mid[]) {
    int i ;
    for(i=0; mid[i] != -1; i++ ) {
        if(pre == *(mid+i))  {
            return i ;
        }      
    }
    return i ;
}

//根据中序和先序创建一颗二叉树
void create_tree(tree*root, int pre[], int mid[]) {
    //每次线序遍历一个元素
    //下表也做相应移动
    static int index  = 0 ;
    int mid_index ;
    //传入先序首元素,在中序列中搜索，记录元素所在的下标
    mid_index = findIndex(pre[index], mid) ;
    root = new tree() ;
    //将节点存在根节点中
    root->i = pre[index] ;
    //将先序已经遍历的元素置为空
    mid[mid_index] = -1 ;
    pre[index] = -1 ;
    //判断那个位置之前是否为空，若非空，说明当前节点有左子树
    //继续递归创建左子树
    if(mid[mid_index-1] != -1) {
        create_tree(root->l, pre, mid) ;
    }
    //否则，就将左孩子设置为空
    else {
        root->l = NULL ;
    }
    //若当前节点的有孩子不为空的
    if(mid[mid_index+1] !='\0') {
        create_tree(root->r, pre, mid) ;
    }
    else {
        root->r = NULL ;
    }
}
