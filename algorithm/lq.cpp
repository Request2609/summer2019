#include <iostream>
using namespace std ;

//本体使用二分查找的思想，不断分半
//计算按照当前这种分法巧克力数量够不够
int calSum(int mid, int days) {
    
    int sum = 0 ;
    //向上取整
    for(int i=0; i<days; i++) {
        sum += mid ;
        mid = (mid%2==0)?(mid/2):(mid/2+1);
    }
    return sum ;
}


int solve(int& cNum, int& days) {
    int first, last, mid, total  ;
    first = 0 ;
    total = cNum ;
    last = cNum ;
    //巧克力的数量连天数都不够
    if(cNum < days) {
        return -1 ;
    } 
    //和天数相等的话，每天吃一片
    if(cNum == days) {
        return 1 ;
    }
    int s = first+last ;
    mid = (s%2==0)? s/2:(s/2+1) ;
    //底线，剩余巧克力数必须为整数
    while(first < last) {
        int sum = calSum(mid, days) ;       
        //吃的的总巧克力数量，少于总巧克力数量，mid应该向上取
        if(sum < total) {
            first = mid;
        }
        else if(sum == total) {
            return mid ;
        }
        else {
            last = mid-1 ;
        }

        int s = first+last ;
        mid = (s%2==0)? s/2:(s/2+1) ;
    }
    return mid ;
}   

int main()
{
    int cNum, days ;
    //输入巧克力的数量和天数
    cin >> days >> cNum;
    int num = solve(cNum, days) ;
    cout << num << endl ;
    return 0;
}

