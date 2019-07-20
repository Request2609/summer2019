#include <iostream>
#include<thread>
#include<future>
using namespace std ;

void initial(std::promise<int>*promObj) {
    cout << "promise thread" << endl ;
    promObj->set_value(34) ;
}

int main()
{
    //主线程创建promise对象，在将对象交给辅助线程之前
    //先获取futrue对象
    //辅助线程获取futrue，并重新设置里面的值
    //主线程在future没有被赋值之前一直是阻塞的
    //创建promise对象
    std::promise<int>promiseObj ;
    //获取future对象
    std :: future<int>futureObj =promiseObj.get_future(); 
   // cout << "线程的值："<< futureObj.get() << endl;
    thread t(initial, &promiseObj) ;

    cout << "赋值完成:" << futureObj.get() << endl ;
    t.join() ;
    return 0;
}

