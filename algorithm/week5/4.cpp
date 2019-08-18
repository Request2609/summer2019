#include <iostream>
/*
 4. 风口之下，猪都能飞。当今中国股市牛市，真可谓“错过等七年”。
给你一个回顾历史的机会，已知一支股票连续 n 天的价格走势，以长
度为 n 的整数数组表示，数组中第 i 个元素（prices[i]）代表该股
票第 i 天的股价。 假设你一开始没有股票，但有至多两次买入 1 股
而后卖出 1 股的机会，并且买入前一定要先保证手上没有股票。若两
次交易机会都放弃，收益为 0。 设计算法，计算你能获得的最大收
益。 输入数值范围：2<=n<=100,0<=prices[i]<=100（题目来源：小
米面试题）
示例:
输入:
3,8,5,1,7,8
输出:
12
 * */
#include <vector>
using namespace std ;
//计算
int calculateMax(vector<int>price){
    int len = price.size() ;
    vector<int>leftMax(10) ;
    vector<int>rightMax(10) ;
    //正序遍历
    int primin = price[0] ;
    leftMax[0] = 0 ;
    for(int i=1; i<len; i++) {
        //记录最小的
        primin = min(primin, price[i]) ;
        //记录第k天第一次交易可以获得的最大收益
        leftMax[i] = max(leftMax[i-1], price[i]-primin) ;
    }
    int primax = price[len-1] ;
    rightMax[len-1] = 0 ;
    for(int i = len-2; i >=0 ; i--) {
        primax = max(primax, price[i]) ;
        //计算第k天之后交易获得的最大结果
        rightMax[i] = max(rightMax[i+1], primax-price[i]) ; 
    }
    
    int pmax = 0 ;
    for(int i=0; i<len; i++) {
        pmax = max(pmax, leftMax[i]+rightMax[i]) ;
    }
    return pmax ;
}

int main()
{
    vector<int>ls ;
    int num ;
    cin>> num ;
    while(num --) {
        int a ;
        cin >> a ;
        ls.push_back(a) ;
    }
    int mm = calculateMax(ls) ;
    cout << mm << endl ;
    return 0;
}
