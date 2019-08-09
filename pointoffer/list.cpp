#include <iostream>
#include <list>
#include<algorithm>
//插入迭代器
using namespace std ;
int main()
{
    list<int>lst = {1,2,3,4} ;
    list<int>lst1, lst2 ;
    //拷贝完成后，lst里面包含4,3,2,1
    copy(lst.cbegin(), lst.cend(), front_inserter(lst1)) ;
    list<int>::iterator iter ;
    for(iter = lst1.begin(); iter!= lst1.end(); iter++) {
        cout << *iter << endl ;
    //正向拷贝
    copy(lst.begin(), lst.end(), inserter(lst2, lst2.begin())) ;
    list<int>::iterator iter1 ;
    for(iter1 = lst2.begin();iter1 != lst2.end(); iter1++) {
        cout<< *iter1 << endl ;
    }
    return 0;
}

