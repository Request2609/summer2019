#include <iostream>
#include <algorithm>
#include <vector>
/*
3. 六一儿童节，老师带了很多好吃的巧克力到幼儿园。每块巧克力
j的重量为 w[j]，对于每个小朋友i，当他分到的巧克力大小达到h[i]
(即 w[j]>=h[i])，他才会上去表演节目。老师的目标是将巧克力分
发给孩子们，使得最多的小孩上台表演。可以保证每个 w[i]> 0 且不
能将多块巧克力分给一个孩子或将一块分给多个孩子。（题目来源：
拼多多面试题）
输入描述:
第一行：n，表示 h 数组元素个数
第二行：n 个 h 数组元素
第三行：m，表示 w 数组元素个数
第四行：m 个 w 数组元素
输出描述:
上台表演学生人数
示例:
输入:
3
2 2 3
2
3 1
输出: 
1
 * */

using namespace std ;

int main() {
    vector<int> nn ;
    int n, m ;
    vector<int> mm ;
    cin >> n ;
    //初始化小孩巧克力满足表演的个数数组
    while(n--) {
        int s ;
        cin >> s ; 
        nn.push_back(s) ;
    }
    cin >> m ;
    //初始化巧克力数组
    while(m--) {
        int s ;
        cin >>s ;
        mm.push_back(s) ;
    }
    int mlen = mm.size() ;
    int nlen = nn.size() ;
    cout << mlen <<endl;
    cout << nlen <<endl ;
    //将小孩数组和巧克力数组从小到大排序
    sort(nn.begin(), nn.end()) ;
    sort(mm.begin(), mm.end()) ;
    int i=0, j =0 ;
    while(i<nlen&&j<mlen) {
        //当前巧克力还不能满足唱歌条件
        if(nn[i] > mm[j]) {
            //让当前小孩拿到巧克力，但还不满足唱歌的条件
            //需要再等下一个巧克力,将小孩满足度降低
            nn[i] -= mm[j] ;
            j++ ;
        }
        //当前巧克力满足唱歌条件,并且条件大于０，将当前巧克力分给小孩
        else if(nn[i] > 0) {
            nn[i] -= mm[j] ;
            j++ ;
        }
        //要是小孩已经满足唱歌条件，将当前小孩忽略，看下一个小孩
        else {
            i++ ;
            continue ;
        }
    }

    int count = 0 ;
    for(int i=0; i<nlen; i++) {
        cout << nn[i] << endl ;
        if(nn[i] <= 0) {
            count++ ;
        }
    }
    return 0; 

}

