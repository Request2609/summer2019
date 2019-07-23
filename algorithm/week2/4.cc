#include <iostream>
#include<string>
#include<algorithm>
using namespace std ;
/*4. 对于字符串 x 和 y, 如果擦除 x 中的某些字母(有可能全擦掉或者
都不擦)能够得到 y,我们就称 y 是 x 的子序列。例如."ncd"是
"nowcoder"的子序列,而"xt"不是。
现在对于给定的一个字符串 s,请计算出字典序最大的 s 的子序列。
（题目来源：百度面试题）
输入描述:
输入包括一行,一个字符串 s,字符串 s 长度 length(1 ≤ length ≤
50). s 中每个字符都是小写字母
输出描述:
输出一个字符串,即字典序最大的 s 的子序列。
示例:
输入:
test
输出:
tt

首先,按字典序排列的最大子序列一定包含最后一个字母

 * */

//先找到字典序最大的子序列，将包含在子序列前面的所有字符擦除掉
//在接着在最大的后面找次大的，知道全找到
void getStr(string& a) {
    char c='\0' ;
    int index ;
    int k = 0 ;
    int len = a.size() ;
    while(k < len-1) {
        for(int i=k; i<len; i++) {
            if(c <= a[i]) {
                c = a[i] ;
                index = i ;
            }

        }
        //找到最大的字符集后，将所有最大字符之前的字符全擦除掉
        for(int i=k; i<index; i++) {
            if(a[i] < c) {
                a[i] = '/' ;
            }
        }
        k = index+1 ;
        //必须将c置为最小
        c = '\0' ;
    }
    for(int i=0; i<len; i++) {
        if(a[i] != '/') {
            cout << a[i] ;
        }
    }   
    cout << endl ;
} 

int main()
{
    string a ;
    cin >> a ;
    getStr(a) ;
    return 0;
}

