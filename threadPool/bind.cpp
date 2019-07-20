#include <iostream>
#include<functional>
using namespace std ;

int func(int a, int b) {
    cout << "a+b的和为:" << a+b << endl ;
    return a+b ;
}

int main()
{
    int a = 1 ;
    int b = 10 ;
    //生成一个函数，返回值为func函数的返回值，不用传参数列表
    auto callFunc = bind(func,a, b)  ;     
    //调用callFunc函数
    int i = callFunc();
    cout << "callFunc函数返回值为:"<< i << endl;
    return 0;
}

