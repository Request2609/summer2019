#include <iostream>
#include<functional>
using namespace std ;
class A {
public :
    void print(A* b, int a) { printf("hello world!%d-------->%d", a, b->aa) ;}
    void change() {
        aa = 10 ;
        auto f = std::bind(&A::print, this,std::placeholders::_1, 1) ;
        f(this) ;
    }

private :
    int aa ;
} ;

int main()
{
    A aa ;
    aa.change() ;
    return 0;
}

