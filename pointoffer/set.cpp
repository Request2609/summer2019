#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std ;

int main()
{
    set<string>ss={"hello", "world", "lala"} ;
    map<string, string>exc = {
        {"hello", "world"} ,
        {"Linux", "Linus"} 
    } ;
    vector<int>ls ;
    while(1) {
        int i ;
        cin >> i ;
        if(i == -1) {
            break ;
        }
        ls.push_back(i) ;
    }
    //将ls中的不重复元素包含进来
    set<int>iset(ls.cbegin(), ls.cend()) ;
    //允许有重复元素，将vector中的所有元素全部包含进来
    multiset<int>miset(ls.cbegin(), ls.cend()) ;
    return 0;
}

