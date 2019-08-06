#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std ;

//前面的pair 为提问者编号，回答人数，最后一个是回答用户的id
map<int, vector<int>> ls  ;
vector<int>cheat ;
map<int, int> ss ;

int isHas(int curId, int dstId) {
    if(ls.find(dstId) == ls.end())  return 0 ;
    vector<int> ll = move(ls[dstId]) ;
    int size = ll.size() ;
    for(int i=0; i<size; i++) {
        if(ll[i] == curId) {
            return 1 ;
        }
    }
    return 0 ;
}

void getRes() {
    map<int, vector<int>>::iterator iter  ;
    for(iter = ls.begin(); iter != ls.end(); iter++) {
        //判断回答人数为1，处理
        int l = iter->second.size() ;
        if(l == 1) {
            int i = iter->second[0] ;
            //判断相应回答对象中有没有当前用户的id
            int ret =  isHas(iter->first ,i) ;
            //最后只看键值就行
            if(ret == 1) {
                ss[i] = iter->first ;
                ss[iter->first] = i;
            }
        }
        else {
            int flag = 1;
            vector<int>h  = iter->second ;
            //要是存在多个解答者，就判断这些解答者与当前解答者的关系
            for(int i=0 ; i<l; i++) {

                if(ss.find(h[i]) == ss.end()) {
                    flag = 0 ;
                    continue  ;   
                }
                else {
                    if(!isHas(h[i], iter->first)) {
                        ss[h[i]] = iter->first ;
                        ss[iter->first] = h[i] ;
                    }
                }
            }
            //设置值为-1
            if(flag == 1) {
                ss[iter->first] = -1 ;
            }
        }
    }
}

int main() {
    int n ;
    cin >>n ;
    
    while(n--) {
        int id ;
        int num ;
        cin >> id ; 
        cin >> num ;
        vector<int>tmp;
        while(num --) {
            int a ;
            cin >>a ;
            tmp.push_back(a) ;
        }
        ls[id] = tmp ;
    }
    getRes() ;
    map<int, int>::iterator iter ;
    vector<int>sss ;
    for(iter = ss.begin(); iter != ss.end(); iter++) {
        sss.push_back(iter->first) ;
    }
    sort(sss.begin(), sss.end()) ;
    int len = sss.size() ;
    cout << len << endl ;
    for(int i=0; i<len; i++) {
        cout << sss[i]<<" ";
    }
    cout << endl ;
    return 0;
}

