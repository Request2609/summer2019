#include <iostream>
#include <string>
#include <vector>
using namespace std ;

string hour, mins,sec ;
void modify(string& tmp) {
    hour = "" ;
    mins ="" ;
    sec = "" ;
    int ret = tmp.find(':') ; 
    if(ret == -1) { return ; }
    hour = tmp.substr(0, ret);

    int res = tmp.rfind(':') ;
    if(ret == -1) {
        return  ;
    }
    int l = res-ret-1 ;
    mins = tmp.substr(ret+1, l) ;
    sec = tmp.substr(res+1, 2) ;
    int hous = atoi(hour.c_str()) ;
    int min = atoi(mins.c_str()) ;
    int seco = atoi(sec.c_str()) ;
    if(hous > 24) {
        hour[0] = '0';
    }
    if(min > 60) {
        mins[0] = '0' ;
    }
    if(seco > 60) {
        sec[0] = '0';
    }
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
        cout << hour<<mins << sec << endl ;
    }
    return 0;
}

