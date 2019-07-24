#include <iostream>
#include<memory>
using namespace std ;
/*struct*/
class A : public enable_shared_from_this<A>{
public :
    A() {
        ss ="hello world" ;
        a = 10 ;
    }

    ~A(){} ;
public :
    shared_ptr<A> getPtr() {
        return shared_from_this() ;
    }
    void print() {
        cout << a  <<" hhhh  " << ss << endl ;
    }

private  :
    int a;
    string ss ;
} ;
int main()
{
    shared_ptr<A> a = make_shared<A>() ;
    shared_ptr<A> s = a->getPtr() ;
    s->print() ;
    a->print() ;
    return 0;
}

