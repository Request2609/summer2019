#include <iostream>
#include <string>
#include <vector>
using namespace std ;

void modify(string& tmp) {
    string hour, mins,sec ;
    int len = tmp.size() ;
 
    cout << tmp << endl ;
    cout << len << endl ;
    int ret = tmp.find(':') ; 
    cout << ret << endl ;
    if(ret == -1) { return ; }
    hour = tmp.substr(0, ret);

    int res = tmp.rfind(':') ;
    cout << res << endl ;
    if(ret == -1) {
        return  ;
    }
    mins = tmp.substr(ret+1, res) ;
    sec = tmp.substr(res+1, len) ;
    cout << hour << mins<< sec<< endl ;
}

int main() {
    
    int num ;
    cin >> num ;
    vector<string>ls ;
    for(int i=0; i<num; i++) {
        string tmp ;
        cin >> tmp ;
        modify(tmp) ;
        ls.push_back(tmp) ;
    }
    return 0;

}

