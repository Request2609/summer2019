#include <iostream>
#include <thread>
#include <vector>
#include <mutex> 
#include <functional>
using namespace std ;
class AA {
private :
    vector<int> ls ;
    mutex mute ;
    int a ;
    thread threads[10] ;
public :    
    void print(int s) {
        a = s;
        cout << "the num is " << a << endl ;
    }

    void threadTest() {
        for(int i=0; i<10; i++) {
            ls.push_back(i) ;
            auto func = bind(&AA::print, this,  placeholders::_1) ;
            threads[i] = thread(func, i) ;
        }
        for(int i=0; i<10; i++) {
            threads[i].join() ;
        }
        for(int i:ls) {
            cout << i << endl ;
        }
    } 
} ;

int main() {
    AA aa ;
    aa.threadTest() ;
}

