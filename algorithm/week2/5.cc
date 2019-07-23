#include <iostream>
#include<vector>
using namespace std ;
/*
 *5. 小易有一个长度为 N 的正整数数列 A = {A[1], A[2], A[3]...,
A[N]}。
牛博士给小易出了一个难题:
对数列 A 进行重新排列,使数列 A 满足所有的 A[i] * A[i + 1](1 ≤
i ≤ N - 1)都是 4 的倍数。
小易现在需要判断一个数列是否可以重排之后满足牛博士的要求。
（题目来源：网易面试题）
输入描述:
输入的第一行为数列的个数t(1 ≤ t ≤ 10), 接下来每两行描述一
个数列 A,第一行为数列长度 n(1 ≤ n ≤ 10^5) 第二行为 n 个正整
数 A[i](1 ≤ A[i] ≤ 10^9)
输出描述:
对于每个数列输出一行表示是否可以满足牛博士要求,如果可以输出
Yes,否则输出 No。
示例:
输入:
2
3
1 10 100
4
1 2 3 4
输出:
Yes
No
 * */

int res = false  ;
void swap(int&i, int& k) {
    int tmp = move(i) ;
    i = move(k) ;
    k = move(tmp) ;
}

//判断是否满足条件
bool isOk(vector<int>ls) {
    int len = ls.size() ;
    for(int i=1; i<len; i++) {
        int s = ls[i-1]*ls[i] ;
        if(s%4 != 0) {
            return false ;
        }
    }
    return true ;
}

//进行全排列，将解空间树列出来，挑出符合条件的即可
void getAnswer(vector<int>ls, int k) {
    int len = ls.size() ;
    if(k==len) {
        res = isOk(ls) ;
        return ;
    }
    //只要得到res为true就行了
    if(res == true) {
        return ;
    }
    for(int i=k; i<len; i++) {
        swap(ls[i], ls[k]) ;
        getAnswer(ls, k+1) ;
        swap(ls[i], ls[k]) ;
    }   
}
int main()
{
    vector<string>result ;
    int num , n;
    cin >> num ;
    while(num) {
        vector<int>a ;
        cin >> n ;
        for(int i=0; i<n; i++) {
            int n ;
            cin >> n ;
            a.push_back(n) ;
        }
        getAnswer(a, 0) ;
        result.push_back(((res==true)?"YES" :"NO")) ;
        res = false ;
        num -- ;
    }
    int len = result.size() ;
    for(int i=0 ; i< len; i++) {
        cout << result[i] << endl ;
    }
    return 0;
}

