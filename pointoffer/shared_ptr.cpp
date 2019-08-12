#include <iostream>
#include <memory>
#include <memory>
using namespace std ;

int main()
{
    shared_ptr<int> p ;
    p.reset(new int(1)) ;
    int* i = p.get() ;
    cout << *i << endl ;
    //w弱共享p,p的引用计数不变
    weak_ptr<int>w(p) ;
    
    return 0;   
}

