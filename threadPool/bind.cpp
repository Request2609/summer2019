#include <iostream>
#include<functional>
using namespace std ;

int func(int a, int b) {
    cout << "a+b的和为:" << a+b << endl ;
    return a+b ;
}

int func1(int a, string b) {
    cout << a << "   " << b << endl ;
    return 1 ;
}

int main()
{
    int a = 1 ;
    int b = 10 ;
    //生成一个函数，返回值为func函数的返回值，不用传参数列表
    auto callFunc = bind(func,a, b)  ;    
    //第一和第二各参数由auto变量指定
    auto callFunc1 = bind(func1,placeholders:: _1,placeholders::_2) ;
    int s = callFunc1(a, "hello");
    cout << s << endl ;
    //调用callFunc函数
    int i = callFunc();
    cout << "callFunc函数返回值为:"<< i << endl;
    return 0;
}

