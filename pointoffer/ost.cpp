#include <iostream>
#include <vector>
#include <iterator>
using namespace std ;

int main()
{
    vector<int>vec{1,2,3,4,5,6,7} ;
    //定义流迭代器
    ostream_iterator<int>out_iter(cout, " ") ;
    //将接受到的数字以空格分隔输出
    for(auto e:vec) {
        *out_iter++ = e ;
    }
    return 0;
}

