#include <iostream>
#include <string>
using namespace std ;
//引用计数
class hasPtr{
public :
    hasPtr(const string&tmp) :ps(new string(tmp)), use(new size_t(1)), i(0) {}
    hasPtr(const hasPtr& ptr): ps(ptr.ps), use(ptr.use), i(ptr.i) { (*use)++ ;}
    //递增右侧对象的引用计数，递减左侧的引用计数
    hasPtr& operator=(const hasPtr&tmp) {
        ++*tmp.use ;
        //递减左侧y引用计数
        if(*--use == 0) {
            delete ps ;
            delete use ;
        }
        ps = tmp.ps ;
        i = tmp.i ;
        use = tmp.use ;
        return *this ;
    }

    ~hasPtr() {}

public :
    int getCount() { return *use ; }
    string getData() { return *ps; }
private :
    string *ps ;
    size_t *use ;
    int i ;
} ;

int main() {
    hasPtr has("hello") ;
    hasPtr hh(has) ;
    
    cout << has.getData() << endl ;
    cout << has.getCount() << endl ;
    cout << hh.getCount()<<endl  ;
    cout << hh.getData() << endl ;
}
