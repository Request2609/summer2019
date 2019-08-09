#include <iostream>
#include <map>
#include <vector>
using namespace std ;

int isExist(vector<int>ls, int k) {
    vector<int>::iterator iter ;
    for(iter = ls.begin(); iter!=ls.end(); iter++) {
        if(*iter == k) {
            ls.erase(iter) ;
            ls.push_back(k) ;
            return 1 ;
        }
    }

    return 0 ; 
}
//使用map存储
int main() {

    int num ;
    cin >> num ;
    vector<int>ls ;
    while(num --) {
        int tmp ;
        cin >> tmp ;
        while(tmp --) {
            int k ;
            cin >> k ;
            if(isExist(ls, k)) {
                continue ;
            }
            else{
                ls.push_back(k) ;
            }
        }
            cout << "修改后的列表！" << endl ;
            int len = ls.size() ;
            for(int i=0; i<len; i++) {
                cout << ls[i] << " " ;
            }
            cout <<"---------------------"<< endl ;
        vector<int>::reverse_iterator iter ;
        for(iter = ls.rbegin(); iter != ls.rend(); iter++) {
            cout << *iter <<" " ;
        }
        cout << endl ;
        ls.clear() ;
    }
    return 0;
}

