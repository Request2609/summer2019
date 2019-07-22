#include <iostream>
/*
 * 2. 牛牛有两个字符串 A 和 B,其中 A 串是一个 01 串,B 串中除了可能
有 0 和 1,还可能有'?',B 中的'?'可以确定为 0 或者 1。 寻找一个字
符串 T 是否在字符串 S 中出现的过程,称为字符串匹配。牛牛现在考
虑所有可能的字符串 B,有多少种可以在字符串 A 中完成匹配。
例如:A = "00010001", B = "??" 字符串 B 可能的字符串是"00","01","10","11",只有"11"没有出现
在字符串 A 中,所以输出 3（题目来源：百度面试题）
输入描述:
输入包括两行,第一行一个字符串 A,字符串 A 长度 length(1 ≤
length ≤ 50),A 中每个字符都是'0'或者'1'。第二行一个字符串 B, 字符串 B 长度 length(1 ≤ length ≤ 50),B 中的字符包括'0','1' 和'?'。
输出描述:
输出一个整数, 表示能匹配的字符串种数。
示例:
输入:
00010001
??
输出:
3
 *
 *
 * */
#include<map> 
using namespace std ;

int solve(string a, string b) {
    int bLen = b.length() ;
    int aLen = a.length() ;
    int bl = bLen ;
    //b串比a串长的话
    if(bLen > aLen) {
        return 0 ;
    }
    map<string, int> mm ;
    //获取可以出现的情况
    for(int i=0; i<aLen; i++) {
        pair<string, int> t ;
        if(i+bLen > aLen) {
            break ;
        }
        string tmp = a.substr(i, bLen) ; 
        t.first = tmp ;
        t.second = 0 ;
        mm.insert(t) ;
    }
    int sum = 0 ;
    int flag ;
    for(pair<string, int>s:mm) {
        flag = 1 ;
        //统计问号的个数
        string&& a = move(s.first) ;
        for(int i=0; i<bl; i++) {
            if(b[i] == '?') {
                continue ;
            }

            if (b[i]!=a[i]) {
                flag = 0 ;
                break ;
            }

        }
        if(flag == 1) {
            sum++ ;
        }
    }
    return sum ;
}

int main()
{
    
    string a,b ;
    cin >> a >> b ;
    int res = solve(a, b) ;
    cout << res << endl ;
    return 0;
}

