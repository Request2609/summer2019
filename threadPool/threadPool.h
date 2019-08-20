#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include<vector>
#include<iostream>
#include<thread>
#include<atomic>
#include<future>
#include<functional>
#include<condition_variable>
#include<queue>
#include<memory>

class threadPool {
public:

    threadPool(unsigned short size) ;
    ~threadPool() ;
public :
    template<class F, class... Args> 
        auto commit(F&& f, Args&&... args)-> std :: future<decltype(f(args...))> ;
public :
    int count() ;
private:    
    //定义线程中的函数类型
    using task = std :: function<void()> ;
    //线程池
    std :: vector<std :: thread>pool ;
    //任务队列
    std :: queue<task> taskQueue ;
    //互斥锁
    std :: mutex muteLock ;
    //条件变量
    std :: condition_variable cond ;
    //开启线程池的句柄，atomic保证了操作stopped的原子性
    std :: atomic<bool> stop;
    //空闲线程数量
    std :: atomic<int> spareThreadNums ;
};

//创建线程池
threadPool :: threadPool(unsigned short size) : stop(false){
    
    spareThreadNums = size<1 ? 10: size ;
    
    for(size = 0; size < spareThreadNums; size++) {
        std :: cout << size << std :: endl ;    
        //初始化线程池，使用lambda表达式
        pool.emplace_back(
                          [this]{
                            //当线程没被终止，等待有任务信号
                          while(!this->stop) {
                          //根据信号
                          //准备接收加入到线程池中的任务并执行    
                          std :: function <void ()> task ;
                          {
                          std :: unique_lock<std :: mutex> lock {this->muteLock} ;
                          //等待条件成立
                          this->cond.wait(lock, 
                                          [this]{ 
                                          return this->stop.load()||!this->taskQueue.empty() ;
                                          }) ;
                          //终止线程池操作
                          if(this->stop && this->taskQueue.empty()) {
                          return ;
                          }
                          //这里使用右值引用，实现０赋值拷贝，提高效率
                          task = std :: move(this->taskQueue.front()) ;
                          this->taskQueue.pop() ;
                          }    
                          spareThreadNums -- ;
                          task() ;
                          spareThreadNums++ ;
                          }                   
                          }
        );
    }
}

//销毁线程池
threadPool :: ~threadPool() {
    stop.store(true) ;
    cond.notify_all() ;
    //等待任务都执行完成统一销毁
    for( std :: thread& t : pool) {
        t.join() ;
    }
}

template<class F, class... Args> 
auto threadPool :: commit(F&& f, Args&&... args)-> std :: future<decltype(f(args...))> {
        
    if(stop.load()) {
        std::cout << "-----" << std::endl ;
       throw std :: runtime_error("线程池已经停止工作")  ;
    }
    //获取函数返回值类型
    using retType = decltype(f(args...)) ;
   //任意参数的函数/任务转化成同意的void()类型的函数，通过task接收
    auto task = std :: make_shared<std :: packaged_task<retType()>> (
                                                                   std :: bind(std :: forward<F>(f), std :: forward<Args>(args)...)                                                             
                                                                     ) ;
    (*task)() ;
    //先获取future
    std :: future<retType> future  = task->get_future() ;
    {
        //对当前语句加锁
        std :: lock_guard<std :: mutex> lock{ muteLock } ;
        //将任务加入到队列中
        taskQueue.emplace(
                          [task](){
                          (*task)() ;
                          }
                          ) ;
    }
    cond.notify_one() ;
    return future ;
}



//空闲线程数量
int threadPool :: count() {
    return spareThreadNums ;
}

#endif
