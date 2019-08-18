#include <iostream>
#include <vector>
using namespace std  ;

vector<int> getRes(int m) {
    int n = m ;
    vector<int>ls ;
    while(n) {
        if(n%2 == 0) {
            ls.push_back(0) ;
            n = n/2 ;
        }
        else {
            ls.push_back(1) ;
            n = n/2 ;
        }
    }
    return ls ;
}

int main() {

    int m, n ;
    cin >> m ;
    cin >> n ;
    vector<int> ls= getRes(m);
    vector<int> ls1 = getRes(n) ;
    int len = ls.size() ;
    int len1 = ls1.size() ;
    int ll = len > len1 ? len1:len ;
    int sum = 0 ;
    for(int i=0; i<ll; i++) {
        if(ls[i] != ls1[i]) {
            sum++ ;
        }
    }
    sum += abs(len-len1) ;
    cout << sum << endl ;
    return 0;
}

