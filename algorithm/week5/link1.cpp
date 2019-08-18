#include <iostream>
#include <stdlib.h>

using namespace std ;

typedef struct link {
    int data ;
    struct link* next ;
} linkNode ;


linkNode* createLink() {
    linkNode* head = NULL ;
    head = (linkNode*)malloc(sizeof(link)) ;
    linkNode*tmp=head ;
    while(1) {
        linkNode* node ;
        node = (linkNode*)malloc(sizeof(linkNode)) ;
        cin >> node->data ;
        if(node->data == -1) {
            free(node) ;
            tmp->next = NULL ;
            break ;
        }
        tmp->next = node ;
        tmp = node ;
    }
    return head ;
}

void print(linkNode* head) {
    linkNode* tmp = head->next ;
    while(tmp) {
        cout << tmp->data << " " ;
        tmp =tmp->next ;
    } 
    cout << endl ;
}

void freeNode(linkNode* head) {
    linkNode* lin = head->next ;
    linkNode * tmp ;
    while(lin) {
        tmp = lin->next ;   
        free(lin) ;
        lin = tmp->next ;
    }  
    
}

void turnBack(linkNode* head) {
    linkNode* tmp = head->next ;
    linkNode* tt = NULL;
    if(tmp) { 
        tt = tmp->next ;
    }
    tmp->next = NULL ;
    linkNode* ll = tt->next ;
    while(1) {
        tt->next = tmp ;
        tmp = tt ;
        tt = ll ;
        if(tt == NULL) {
            break ;
        }
        ll = tt->next ;
    }   
    head->next = tmp;
}

int main() {
    linkNode* head = createLink() ;
    cout <<"逆置前：" << endl ;
    print(head) ;
    turnBack(head) ;
    cout << "逆置后：" << endl ;
    print(head) ;
    freeNode(head) ;
    return 0;
}

