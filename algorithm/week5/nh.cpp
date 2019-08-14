#include <iostream>
#include <vector>
using namespace std ;
/*
 1. 有 N 个孩子站成一排，每个孩子有一个分值。给这些孩子派发糖
果，需要满足如下需求：
1、每个孩子至少分到一个糖果
2、分值更高的孩子比他相邻位的孩子获得更多的糖果
1. 求至少需要分发多少糖果？（题目来源：美丽联合面试题）
输入描述:
0,1,0
输出描述:
4
示例:
输入:
5,4,1,1
输出:
7
 * */
vector<pair<int, int>> ls ;
int sum ;

int getRes() {
    int len = ls.size() ;
    //从第二个小孩开始遍历
    for(int i=0; i<len-1; i++) {
        if(ls[i].first > ls[i+1].first&&ls[i].second <= ls[i+1].second) {
            ls[i].second+=1 ;
        }
        if(ls[i].first < ls[i+1].first&&ls[i].second<=ls[i+1].second) {
            ls[i+1].second+=1 ;
        }
        if(i-1 >=0&&ls[i-1].first > ls[i].first&&ls[i-1].second == ls[i].second) {
            ls[i-1].second++ ;
        }
    }
    for(int i=0; i<len; i++)  {
        sum+=ls[i].second ;
    }  
    return sum ;
}

int main() {

    int  n ;
    cin >> n ;
    while(n--) {
        int a ;
        cin >> a ;
        ls.push_back(make_pair(a, 1)) ;
    }   
    getRes() ;
    cout << sum << endl ;
    return 0;
}

