#include <iostream>
#include <vector>
using namespace std  ;
/*
面试题8 旋转数组的最小数字
题目：

把一个数组的最开始的若干元素搬到数组的末尾，我们称之为数组的旋转。
输入一个**递增排序【更准确的说法是 非递减排序，
本题目的难点就是需要考虑各种特殊情况】**的数组的一个旋转，输出旋转数组的最小元素。
例如，数组 {3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
*/

vector<int>ls ;
//获取结果
int getRes() {
    int len = ls.size() ; 
    int start = 0 ;
    int end = len-1;
    int mid = (0+len)/2;
    while(1) {
        //如果中间元素位于数组的前半部分，则中间元素应该大于第一个元素
        //可以移动头指针
        //满足条件说明中间元素属于前半部分
        cout << start << "                  " << end << endl  ;
        if(ls[start] < ls[mid] && ls[mid] > ls[end]) {
            start = mid+1 ;
        }
        //前面指针指向的元素小于中间元素并且中间元素小于末尾元素
        else if(ls[start] <= ls[mid] && ls[mid] <= ls[end]) {
            end = mid ;
        }
        else if(ls[start] > ls[mid]){
            start = mid ;
        }

        mid = (end+start)/2 ;
        if(start == end) {
            break ;
        }
    }
    return ls[start] ;
} 

int main() {
    while(1) {
        int a ; 
        cin >> a ;
        if(a == -1) {
            break ;
        }
        ls.push_back(a) ;
    }
    int ret = getRes() ;
    cout << ret << endl ;
    return 0;
}

