#include <iostream>
#include <vector>
using namespace std ;
/*
  * 面试题4: 替换空格
 * 题目： 请实现一个函数，把字符串中的每个空格替换成 "%20"。
 *       例如输入 "We are happy."，则输出"We%20are%20happy."。
 * */

void func(string a) {
    
    int i = 0 ;
    while(1) {
        int len = a.size() ;
        if(a[i] == ' ') {
           a.replace(i, 1, "%20") ; 
            i+=3 ; 
        }
        else {
            i++ ;
        }
        if(i > len) {
            break ;
        }
    }
    cout << a << endl ;
}

int main() {
    func("hello world Linux") ;
}
