#pragma once
#include<atomic>
#include<string>
#include<map>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std ;
//pair第一项是姓名，第二项是mac
map<int, pair<string, string>> userList ;

//这里初始化mac地址表

void getUserMac() {
    ifstream in("mac.txt") ;
    while(!in.eof()) {

        pair<int, pair<string, string>> s ;
        in>>s.second.first>>s.second.second ;
        userList.insert(s) ;
    }
    in.close() ;
}

//遍历一次mac表，看存不存在ｍａｃ，存在的话，将对应的计数器加１
//否则，将对应的计数器不变:
void macExist(string& mac) {
    getUserMac() ;
    
    for(pair<int, pair<string, string>>s:userList) {
        if(mac == s.second.second) {
            s.first ++ ;
            cout << s.first << "     " << s.second.first << "     " << s.second.second << endl ;
            break ;
        }
    }
    //这里可以给排个序
}


