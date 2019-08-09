#include <iostream>
#include <stack>
using namespace std ;
/*
输入一个链表的头结点，从尾到头反过来打印出每个结点的值（不能改变链表的结构，仅仅对链表进行只读操作）
 * */
//知识点：栈的应用
//假设链表为单向链表，头结点为空
struct link {
    int i ;
    link* next ;
} ;
void print(link* s) {
    stack<link*>st ;
    link * ss = s->next ;
    while(ss) {
        st.push(ss) ;
        ss = ss->next ;
    }
    //从头逐个弹出链表中的元素
    while(!st.empty()) {
        link*l = st.top() ;
        cout <<l->i << endl ;
    }
}
