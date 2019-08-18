#include <iostream>
#include <vector>
using namespace std ;

void swap(int& start, int& end) {
    int tmp = 0 ;
    tmp = move(start) ;
    start = move(end) ;
    end = move(tmp) ;
}

void getRes(vector<int>&ls) {
    int len = ls.size() ;
    int start=-1 ;
    int end=len;
    //将数组中的奇数排在前面，偶数排在后面
    while(1) {
        //前面找偶数
        for(int i = start+1; i<len; i++) {
            //是偶数
            if(ls[i]%2 != 1) {
                start = i ;
                break ;
            }
        }
        //从后往前找奇数
        for(int i=end-1; i>=0; i--) {
            if(ls[i]%2) {
                end = i ;
                break ;
            }
        }
        if(start >= end) {
            break ;
        }
        swap(ls[start], ls[end]) ;
    }
}
int main() {
    vector<int>ls ;
    while(1) {
        int a ;
        cin >> a ;
        if(a == -1) break ;
        ls.push_back(a) ;
    }
    getRes(ls) ;
    int len = ls.size();
    for(int i=0; i<len; ++i) {
        cout << ls[i] << "  " ;
    }
    cout << endl ;
    return 0;
}

