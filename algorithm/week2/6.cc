#include <iostream>
#include<map>
#include<queue>
using namespace std ;
/*
6. 小招喵喜欢在数轴上跑来跑去，假设它现在站在点 n 处，它只会
3 种走法，分别是：
1.数轴上向前走一步，即 n=n+1
2.数轴上向后走一步,即 n=n-1
3.数轴上使劲跳跃到当前点的两倍，即 n=2*n
现在小招喵在原点，即 n=0，它想去点 x 处，快帮小招喵算算最快的
走法需要多少步？（题目来源：招商面试题）
输入描述:
小招喵想去的位置 x
输出描述:
小招喵最少需要的步数
示例:
输入:
3
输出:
3
 * */


int getRes(int dst) {
    //第一个为level为所走的步数，第二个为在本层中的结果
    queue<pair<int, int>> q ;
    pair<int, int> tmp ;
    //小招秒走了第０步
    tmp.first = 0 ;
    tmp.second = 0 ;
    q.push(tmp) ;
    //队列不为空的话，就尝试三种方法
    //将各种结果加入队列
    while(!q.empty()) {
        pair<int, int> t = q.front();
        //小招秒走了第０步
        int tmp ;
        tmp = t.second+1 ;
        if(tmp == dst) {
            cout << "======" << tmp << endl ;
            return t.first+1; 
        }
        else {
            //不等就继续往下走
            q.push(make_pair(t.first+1, t.second+1)) ;  
        }
        tmp = t.second-1 ;
        if(tmp == dst) {
            cout << "==----==" << tmp << endl ;
            return t.first+1 ;
        }
        else {
            q.push(make_pair(t.first+1, t.second-1)) ;  
        }
        tmp = t.second*2 ;
        if(tmp == dst) {
            cout << "==****==" << tmp << endl ;
            return t.first+1 ;
        }
        else {
            q.push(make_pair(t.first+1, t.second*2)) ;  
        }   
        q.pop() ;
    }
    return -1 ;
}      
//队列，广度搜索
int main() {
    int n=0 ;
    cin >> n; 
    int res = getRes(n) ;
    if(res == -1) {
        cout <<"the Dest place can't get" << endl ;
    }
    else {
        cout << res << endl ;
    }
    return 0;
}

