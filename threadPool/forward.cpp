#include <iostream>
using namespace std ;

class A {
private :
    int k ;
public : 
    A() {
        cout << "construct " << endl ;
    }
    ~A() {
        cout << "destruct" << endl ;
    }
} ;

void print(int& v) {
    cout << "value=" << v << endl ;
}
void processLValue(int& i) {
    i = 10 ;
    cout << "LValue:" << i << endl ;
}
void processRValue(int && i) {
    i = 9 ;
    cout << "Rvalue:"  <<i << endl ;
}

//move 实现swap函数，避免了三次不必要的拷贝动作
void swap(int& a, int& b) {
    int tmp(move(a)) ;    
    a = move(b) ;
    b = move(tmp) ; 
}
//move实现了把左值引用当做右值引用来使用，避免了不必要的赋值拷贝
//完美转发：精确传递
//需要将一组参数原封不动的传给另一个函数
//完美转发
void test(int i) {
    cout << i << endl ;
    i = 19 ;
    cout << i << endl ;
}

//右值引用
void forwardTest(int&& i) {
    //如果传给forwardTest的是一个左值的话，就以左值的形式传给test，要是右值的话，将参数以以右值的形式传给test
    test(forward<int>(i));
}

int main()
{
  ///  testForward(1) ;
    int x = 1; 
    processLValue(x) ;
    cout << x << endl ;
    processRValue(move(x)) ;    
    cout << x << endl ;
    int a= 1, b=3 ;
    cout << a <<"----" << b << endl ;
    swap(a, b) ;
    cout << a<< "----" << b << endl;
    //完美转发
    forwardTest(move(b)) ;
    return 0;
}

