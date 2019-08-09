#include <iostream>

#include<string>
using namespace std ;

int main()
{
    string a = "hello wor ld!"  ;
    string s ;
    //将原先字符串清空的重新作赋值
    s.assign(a, 5) ;
    cout << s << endl ;
    s.assign("hello") ;
    cout << s<< endl ;
    a.replace(5, 1, "%") ;
    cout << a << endl ;
    //指定从什么位置开始找
    cout << a.find(" ", 6) << endl  ;
    
    return 0;
}

