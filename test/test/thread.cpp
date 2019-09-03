#include <iostream>
#include <thread>
using namespace std ;

void func() {
    cout << "hello world!" << endl;
}
int main() {
    
    thread tt[5] ;
    cout << "five thread running !" << endl ;
    cout << tt[0].get_id() << endl ;
    cout << tt[1].get_id() << endl ;
    cout << tt[2].get_id() << endl ;
    cout << tt[3].get_id() << endl ;
    cout << tt[4].get_id() << endl ;

    for(int i=0; i<5; i++) {
        tt[i] = thread(func) ;
    } 
    for(int i=0; i<5; i++) {
        tt[i].join() ;
    }
    return 0;
}

