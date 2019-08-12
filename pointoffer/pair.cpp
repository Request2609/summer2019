#include <iostream>
#include <vector>
#include <set>
#include<map>
using namespace std ;
    
pair<string, int>process(vector<string>ls) {
    if(!ls.empty()) {
        return {ls.back(), ls.back().size()} ;
    }
    else {
        return pair<string, int>() ;
    }
}
//遍历关联容器
int main()
{   
    map<int, string> ls = {
        {1, "hello"},
        {2, "world"} 
    };
    auto s = ls.cbegin() ;
    while(s != ls.cend()) {
        cout << s->second ;
        s ++ ;
    }
    //set插入算法
    vector<int>ss {1,2,3,4,5}  ;
    set<int>se ;
    se.insert(ss.cbegin(), ss.cend()) ;
    
    return 0;
}

