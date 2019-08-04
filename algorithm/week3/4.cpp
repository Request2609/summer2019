#include <iostream>
#include <algorithm>
using namespace std ;
/*
4. 假设一个探险家被困在了地底的迷宫之中，要从当前位置开始找
到一条通往迷宫出口的路径。迷宫可以用一个二维矩阵组成，有的部
分是墙，有的部分是路。迷宫之中有的路上还有门，每扇门都在迷宫
的某个地方有与之匹配的钥匙，只有先拿到钥匙才能打开门。请设计
一个算法，帮助探险家找到脱困的最短路径。如前所述，迷宫是通过
一个二维矩阵表示的，每个元素的值的含义如下 0-墙，1-路，2-探
险家的起始位置，3-迷宫的出口，大写字母-门，小写字母-对应大写
字母所代表的门的钥匙。（题目来源：拼多多面试题）
输入描述:
迷宫的地图，用二维矩阵表示。第一行是表示矩阵的行数和列数 M 和
N 后面的 M 行是矩阵的数据，每一行对应与矩阵的一行（中间没有空
格）。M 和 N 都不超过 100, 门不超过 10 扇。
输出描述:
路径的长度，是一个整数
示例:
输入:
5 5
02111
01a0A
01003
01001
01111
输出:
7
 * */
#include<queue>
#include<string.h>
#include<memory>
#include<map>
#define N 1000
using namespace std ;
//路径中的每个节点
struct wayNode {
    int x ;
    int y ;
    shared_ptr<wayNode> prev ;
} ;

//表示有钥匙的话，置为1没钥匙的话置为０,默认没钥匙
int flag ;
int width, height ;
char a[N][N] ;
int startx, starty ;
//钥匙状态以及要是名称
//要是名称，要是坐标，以及标记
map<char, pair<wayNode, int>>keys ;
//记录路径的点
//现将所有钥匙收集起来
//广度优先搜索，判断每一个点只要是２或者碰到门以后，判断要是状态为已经拿到，则可以出迷宫
void func(int x, int y, queue<pair<int, int>>&q) {
    pair<int, int>tmp ;
    tmp.first = x ;
    tmp.second = y ;
    q.push(tmp) ;
}

int isOk(int x, int y) {
    if(x>0&&x<=width&&y>0&&y<=height) {
        return 1 ;
    }
    return 0 ;
}
int isChar(char ch) {
    if(ch>='a'&&ch<='z') {
        return 1 ;
    }
    return 0 ;
}

int isDoor(char ch) {
    if(ch<='Z'&&ch>='A') {
        return 1 ;
    }
    return 0 ;
}

//返回一就表明找到了终点
int judge(char ch, int x, int y, queue<pair<int, int>>&q) {
    if(ch == '1') {
        func(x, y, q) ;
    }
    if(isChar(ch)) {
        //捡起钥匙
        keys[ch].second = 1 ;
        func(x, y, q) ;
    }
    if(isDoor(ch)) {
        //遇到了门，看要是是否已经找到了，找到就返回
        if(keys[ch].second) {
            return 1 ;
        }
    }

    if(ch == '3') {
        return 1 ;
    }
    return 0 ;
}

//传入起点坐标终点和起点到终点标志，统计起点到终点的最短步数
int getBestRes() {
    queue<pair<int, int>> q ; 
    shared_ptr<wayNode>way ;
    int count = 1;
    //如果标志位为０,找终点
    //队列非空
    q.push(make_pair(startx, starty)) ;
    //记录第一个节点
    while(!q.empty()) {
        //获取队列头部的元素
        pair<int, int> tmp = q.front() ;
        q.pop() ;
        int x = tmp.first ;
        int y = tmp.second ;
        cout <<x << "     " << y << endl ;
        //完成一层的搜索
        if(x == 0 || y == 0) {
            count ++ ;
            continue ;
        }
        
        //向四个方向探索，左，下，右，上
        //能走通，记录路径并加入到队列中
        int ret = 0 ;
        if(ret!=1&&isOk(x+1, y)&&a[x+1][y] != '0') {
            char ch = a[x+1][y] ;
            ret = judge(ch, x+1, y, q) ;
            a[x+1][y] = '0';
            //如果是１，直接加入到队列中
        }
        //下面的为１，行的通的话
        if(ret!=1&&isOk(x, y+1)&&a[x][y+1] != '0') {
            char ch = a[x][y+1] ;
            ret = judge(ch, x, y+1, q) ;
            a[x][y+1] = '0' ;
        }

        if(ret!=1&&isOk(x-1, y)&&a[x-1][y] != '0') {
            char ch = a[x-1][y] ;
            ret = judge(ch, x-1, y, q) ;
            a[x-1][y] = '0' ;
        }

        if(ret!=1&&isOk(x, y-1)&&a[x][y-1] != '0') {
            char ch = a[x][y-1] ;
            ret = judge(ch, x, y-1, q) ;
            a[x][y-1] = '0' ;
        }  
        if(ret == 1) {
            return count ;
        }
        //将四个方向遍历完成后
        //用分层的方式分割
        func(0, 0, q) ;
    }
    return 0 ;
}

int main() {
    //迷宫的长宽
    cin >> width ;
    cin >> height ;
    //初始化
    for(int i=1; i<=width; i++) {
        for(int j=1; j<= height; j++) {
            cin>>a[i][j] ;
            //记录起点和终点的坐标
            if(a[i][j] == '2') {
                startx = i ;
                starty = j ;
            }
            //先收集所有的钥匙吧!
            if(isChar(a[i][j])) {
                pair<char, pair<wayNode, int>> tmp ;
                wayNode  s ;
                s.x = i ;
                s.y = j ;
                tmp.first = a[i][j] ;
                tmp.second = make_pair(s, 0) ;
            } 
        }
    }
    cout << startx << "        " <<starty <<endl ;
    //先找出起点到终点的最短路径
    cout << getBestRes() << endl ;
    return 0;

}

