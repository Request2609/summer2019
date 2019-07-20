#include <iostream>
#include<functional>
#include<future>
#include<thread>
#include<chrono>
using namespace std ;

int test(int a, int b, int& val) {
    //设置超时，突出效果
    this_thread::sleep_for(chrono::seconds(5)) ;
    cout << "设置future变量的值" << endl;
    return val+a+b ;
}

int main()
{
    
    packaged_task<int(int, int, int&)>pt(test) ;
    future<int>f = pt.get_future() ;
    int c = 1000;
    //将pt及对应的参数放到线程中
    thread t(move(pt), 100, 2000, ref(c)) ;
    int iResult = f.get() ;
    t.join() ;

    cout << iResult << endl ;
    return 0;
}

