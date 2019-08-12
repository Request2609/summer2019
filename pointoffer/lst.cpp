#include <iostream>
#include <list>
using namespace std ;

int main()
{   
    list<int>ls ;
    while(1) {
        int i ;
        cin >> i ;
        if(i == -1) {
            break ;
        }
        ls.push_back(i) ;
    }
    list<int>ls1 ;
    while(1) {
        int i ;
        cin >> i ;
        if(i == -1) {
            break ;
        }
        ls1.push_back(i) ;
    }
    //逆置链表
    ls.reverse() ;
    //将ls1和ls合并，排好后整体是有序的
    ls.merge(ls1, [](int a, int b){return a>b ;}) ;
    return 0;
}

