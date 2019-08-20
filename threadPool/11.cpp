#include <iostream>
#include <future> 
#include <functional>
using namespace std ;
//提交事务
//返回future 类型后，可以将线程执行的任务返回值返回给线程池的线程
template<class F, class... Args> 
auto commit(F&& f, Args&&... args)-> std :: future<decltype(f(args...))> {
    
    /*if(stop.load()) {
        std::cout << "-----" << std::endl ;
       throw std :: runtime_error("线程池已经停止工作")  ;
    }*/
    //获取函数返回值类型
    using retType = decltype(f(args...)) ;
   //任意参数的函数/任务转化成同意的void()类型的函数，通过task接收
    auto task = std :: make_shared<std :: packaged_task<retType()>> (
                                                                   std :: bind(std :: forward<F>(f), std :: forward<Args>(args)...)                                                             
                                                                     ) ;
    (*task)() ;
    //先获取future
    std :: future<retType> future  = task->get_future() ;
    /*{
        //对当前语句加锁
        std :: lock_guard<std :: mutex> lock{ muteLock } ;
        //将任务加入到队列中
        taskQueue.emplace(
                          [task](){
                          (*task)() ;
                          }
                          ) ;
    }
    cond.notify_one() ;*/
    return future ;
}

void func(int i) {
    std :: cout << "该函数返回值为void，传的参数是" << i << std :: endl ;
}

int func2(int a, int b) {
    std :: cout << "有个返回值的线程池" << "  int"<< std :: endl ;
    return a+b ;
}

int main() {

    future<void>ff  = commit(func, 1) ;
    future<int>ff1  = commit(func2, 1, 2) ;
    
    cout << "ff2= " << ff1.get() << endl  ;
    
    return 0;
}

