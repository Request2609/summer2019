#include <iostream>
#include<boost/thread/thread.hpp>
#include<atomic>
#include<thread>
using namespace std ;
//使得total 具有原子操作
atomic_long total(0) ;

void tick() {
    for(int i=0; i<10000; i++) {
        total+=i ;
    }
}

int main()
{
    boost:: thread_group threads ;
    for(int i=0; i<100; i++) {
        threads.create_thread(tick) ;
    }
    threads.join_all() ;
    cout << total<< endl ;
    return 0;
}

