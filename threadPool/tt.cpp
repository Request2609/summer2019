#include <iostream>
#include<functional>
#include<future>
#include<memory>
using namespace std ;
int func(int i) {
    cout << "传进来的参数值为："<< i << endl ;
    return i ;
}

auto func1(int i) ->std::future<int> {

    using type = int ;
    auto task = make_shared<packaged_task<type()>> (
                std::bind(forward<int(int i)>(func), std::forward<int>(i)) 
                ) ;
      std::future<int> futures = task->get_future();
      (*task)() ;
      return futures ;
}
int main()
{
    func1(1) ;
    return 0;
}

