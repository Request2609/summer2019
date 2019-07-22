#include <iostream>
/*
 * 1. 牛牛对整除非常感兴趣。牛牛的老师给他布置了一道题：牛牛的
老师给出一个 n,然后牛牛需要回答出能被 1 到 n 之间（包括 1 和 n）
所有整数整除的最小的数。牛牛犯了难，希望你能编程帮他解决这个
问题。（题目来源：京东面试题）
输入描述:
输入包括一个整数 n(1<=n<=100000)
输出描述:
输出一个整数，即满足要求的最小整数。答案可能很大，请输出这个
整数对于 987654321 取模的结果
示例:
输入:
3
输出:
6
 * */
using namespace std ;

int solve(int n) {
    int16_t m = n ;
    int16_t i = 2 ;
    while(1) {
        int16_t flag = 1 ;
        for(int16_t j=n; j>0; j--) {
            if(m%j != 0)  {
                flag = 0 ;
                break ;
            }
        }
        //满足条件直接返回
        if(flag == 1) {
            return m ;
        }
        else {
            m = n*i ; 
            i++ ;
        }
    }
}

int main()
{
    int16_t n ;
    cin >>n ;
    int16_t res = solve(n) ;
    int s = res%987654321 ;
    cout << s << endl ;
    return 0;
}

