#include <iostream>
#include<string>
#include<algorithm>
using namespace std ;

void changeStr(string& a, string& b) {
    //给b字符串降序排序
    sort(b.rbegin(), b.rend()) ;
    int aLen = a.length() ;
    int bLen = b.length() ;
    if(aLen < bLen) {
        return ;
    }

    int i = 0 ; 
    int j = 0 ;
    while(j<bLen) {
        if(a[i] < b[j]) {
            a[i] = b[j] ;
            j++ ;
        }
        i++ ;
    }
}

int main()
{
    string a, b ;
    cin >> a >> b ;
    changeStr(a, b) ;
    cout << a << endl ;
    return 0;
}

