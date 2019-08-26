#include <iostream>
#include <memory>
using namespace std ;
//c++ 内存分配

int main() {
    allocator<string>alloc ;//可分配string 的allocator对象
    auto const p = alloc.allocate(10) ;//分配n个未初始化的string   
    auto q = p ;
    alloc.construct(q++) ;//ｑ为空字符串
    alloc.construct(q++, 10, 'c') ;//*q为ccccccccc字符串
    alloc.construct(q++, "hello world") ;
    //输出构造的字符串,并释放内存
    while(q != p) {
        cout << *--q << endl ;
        alloc.destroy(q) ;
    }   
    return 0;
}

