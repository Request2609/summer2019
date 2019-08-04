#include <iostream>
/*
1. 给定一个无序数组，包含正数、负数和 0，要求从中找出 3 个数
的乘积，使得乘积最大，要求时间复杂度：O(n)，空间复杂度：O(1)
（题目来源：拼多多面试题）
输入描述:
无序整数数组 A[n]
输出描述:
满足条件的最大乘积
示例:
输入:
3 4 1 2
输出:
24
*/
#include<vector>
#include<algorithm>
using namespace std ;

int main() {

    vector<int> arr ;
    int l ;
    while(1) {
        cin >> l ;
        if(l == -1) {
            break ;
        }
        arr.push_back(l) ;
    }   
    //排序，最大值要么是最大的三个乘积
    //要么是最小的两个和最大的乘积
    sort(arr.rbegin(), arr.rend()) ;
    int len = arr.size() ;
    int tmp1 = arr[0]*arr[1]*arr[2] ;
    int tmp2 = arr[0]*arr[len-1]*arr[len-2] ;
    cout << (tmp1>tmp2?tmp1:tmp2) <<endl ;
    return 0;
}

