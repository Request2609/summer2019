#include"threadPool.h"
#include<iostream>

void func(int i) {
    std :: cout << "该函数返回值为void，传的参数是" << i << std :: endl ;
}

int func2(int a, int b) {
    std :: cout << "有个返回值的线程池" << "  int"<< std :: endl ;
    return a+b ;
}

struct gfunc{
    int operator()(int n) {
        std::cout << n << std::endl ;
        return n ;
    }
    int func() {
        printf("hello " ) ;
        return 1 ;
    }
} ;

int func1(std :: string a, int b) {
    std :: cout << "字符串的值为:" << a << "    整型值为：" << b << std :: endl ;  
    return 0 ;
}

int main()
{
    try {
        //线程池队列正在等待
        threadPool pool(10) ;
        //往队列中加入任务
        std :: future<void> ff = pool.commit(func, 1);       
        std :: future<int> ff1 = pool.commit(func2, 1,2) ;
        std :: future<in> ff2 = pool.commit(gfunc{},2) ;
        pool.commit(gfunc::func) ;
        printf("ff:") ;
        ff.get();
        printf("ff1:") ;
        ff1.get() ;
        printf("ff2:") ;
        ff2.get() ;
    } catch(std :: exception& e) {
        std :: cout << "some unhappy happened..." << std :: this_thread :: get_id() << e.what() << std :: endl ;
    }
    return 0;
}

