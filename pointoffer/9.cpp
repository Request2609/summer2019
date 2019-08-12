#include <iostream>
/*
 写一个函数，输入 n，求斐波那契 (Fibonacci)数列的第 n 项。
 斐波那契数列的定义如下： f(n) = 0, n = 0

f(n) = 1, n = 1

f(n) = f(n-1) + f(n-2), n > 1
 */
#include <vector>
using namespace std  ;
vector<int>ls ;
int a[100] ;

int func(int n) {
    if(n==1|| n==0) {
        return n ;
    }
    //当数组中的n为下标已经计算过，就不用计算
    if(a[n] > 0) {
        return a[n] ;
    }
    //使用数组记录前面计算的解
    a[n] = func(n-1)+func(n-2) ;
    return a[n] ;
}
int main() {
    int n ;
    cin >> n ;
    //当输入的数组大于1时，保存前三个元素
    cout <<  func(n)  << endl ;  
    return 0;
}

