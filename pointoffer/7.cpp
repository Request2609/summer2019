#include <iostream>
#include <stack>
/*
用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead
分别完成在队列尾部插入结点和在队列头部删除结点的功能//
//存元素的时候可以给A中存，取元素的时候可以从B中取
*/


using namespace std ;
class que{
    //加元素的栈尾部元素是队尾
    stack<int>lsPush ;
    //删除元素的栈的栈顶元素是队头
    stack<int>lsPop ;
public :
    //弹出队列中的元素
    int  pop() {
        if(!lsPop.empty()) {
            int a = lsPop.top() ;
            lsPop.pop() ;
            return a ;
        }
        else {
            if(!lsPush.empty()) {
                lsPop.push(lsPush.top()) ;
                lsPush.pop() ;
            }
            else {
                int a = -1;
                return a ;
            }
            int a = lsPop.top() ;
            lsPop.pop() ;
            return a ;
        }
    }
    //存元素，存元素之前将当前队列中元素先移动到lspop中
    int push(int a) {
        //将lsPop队列中的元素先转移到lsPush
        if(!lsPop.empty()) {
            int s = lsPop.top() ;
            lsPop.pop() ;
            lsPush.push(s) ;
        }
        else {
            lsPush.push(a) ;       
        }
        return 1 ;
    }
    int size() {
        return lsPop.size() + lsPush.size() ;
    }

    int front() {
        if(!lsPop.empty()) {
            return lsPop.top() ;
        }
        else {
            if(!lsPush.empty()) {
                return lsPush.top() ;
            }
            else {
                int a = -1;
                return a ;
            }
        }
    }
    bool empty() {
        return lsPop.size()||lsPush.size() ;
    }
} ;

int main() {
    que q ;
    //注意先后顺序
    q.push(2) ;
    q.push(4) ;
    q.push(1) ;
    cout << q.pop() << endl ;
    cout << q.pop() << endl ;
    cout << q.pop() << endl ;
    return 0;
}

