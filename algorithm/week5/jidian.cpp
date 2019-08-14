#include <iostream>
#include <set>
/*
 2. 有 n 个 1~23 的整数，写一个算法，求出有多少个相互不同的子集
合的和为 24 点。（题目来源：小米面试题）
输入描述:
输入数据包含一组
每组的第一行包括一个整数 n(1 <= n <= 23)
第二行包括 n 个整数 1 <= 整数 <= 23）
输出描述:
对于每个测试实例，要求输出能组成 24 点的所有子集合的数量（子
集合相互不同）。如果不存在，则输出 0。每个测试实例的输出占一
行。
示例:
输入:
4
1 2 22 23
输出:
2
 * */
#include <vector>
using namespace std ;
//dfs
vector<int>ls ;
int sum ;
int count ;
void dfs(int index, int& s, int num) {
    cout << "-------" << s << endl ;
    if(s == 0) {
        count++ ;   
        return ;
    }
    if(s < 0|| index>=num) {
        return  ;
    }
    dfs(index++, s, num) ;
    int aa = ls[index] ;
    dfs(index++, s-ls[index], num) ;
}

int main() {
    int n ;
    cin >> n ;
    while(n--) {
        int a ;
        cin >> a ;
        ls.push_back(a) ;      
    }

    int len = ls.size() ;
    for(int i=0; i<len; i++) {
        sum = 24 ;
        dfs(i,sum, len) ;
    }
    cout << count << endl ;
    return 0;
}

