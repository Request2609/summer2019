#include <iostream>
using namespace std ;

int func(int i) {
    return i+10 ;
}

//已经转换成左值了
int test(int k) {
    cout << k << endl ;
    return k ;
}

void relay(int&& i) {

    //这个函数直接将i原来的右值变成了左值
    test(i) ;  
    
    //forward完美转发
    //i传进来是右值
    test(forward<int>(i)) ;
}

int main()
{
    relay(func(10)) ;
    return 0;
}

