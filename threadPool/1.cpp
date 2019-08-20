#include <iostream>
#include <functional>
#include <memory>
#include <future>

using namespace std ;

//可以传任意参数的函数
template <class F, class... Args> 
auto commit(F&& f, Args&&... args)->future<decltype(f(args...))> {
    //获取函数指针类型
    using retType = decltype(f(args...)) ;
    //将任意提参数类型的函数转化成void类型
    //auto task = make_shared<packaged_task<retType()>>(bind(forward<F>(f), forward<Args>(args)...));
    //auto func = bind(forward<F>(f), forward<Args>(args)...) ;
    //将可调用实体
    packaged_task<retType()> tasks (bind(forward<F>(f), forward<Args>(args)...)) ;
    //先获取futrue
    future<retType>futures= tasks.get_future() ;
    //将转化后的函数返回   
    try {
        tasks() ; 
    }catch(exception& e) {
        cout<< "异常信息：" << e.what()<< endl ;
    }
    return futures ;
}

void  func() {
    cout << "hello world!" << endl ;
}


int funcs(int i) {
    cout << "hello" <<"-------->" <<"No." << i << endl ;
    return i ;
}

int main() {
    auto fu = commit(funcs, 1);
    cout << fu.get()  << endl ;
    getchar() ;
    return 0;   
}

