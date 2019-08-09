#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;

int main()
{
    vector<int>a{1,2,3,4,5} ;
    //在容器中查找该元素
    auto ret = find(a.cbegin(), a.cend(), 2) ;
    string aa = (ret == a.cend()?"No the num" : "has the num") ;
    cout << aa << endl ;
    int ls[] = {23, 24, 45, 56, 57} ;
    int val = 73 ;
    //在整数数组中查找元素
    //未找到就返回－１
    int *result = find(begin(ls), end(ls), val) ;
    cout << *result << endl ;
    //容器求和
   // int res = accumulate(a.cbegin(),a.cend(), 0) ;
    //将容器中的元素全部设置为10
    fill(a.cbegin(), a.cend(), 10) ;
    //添加是个元素到vector a
    fill_n(back_inserter(a), 10, 0) ;
    //拷贝算法,将ss中的元素拷贝给a2
    int ss[] = {1, 2,3,4,4} ;
    int a2[sizeof(ss)/sizeof(*ss)] ;
    copy(begin(ss), end(ss), a2) ;
    return 0;
}

