#include <iostream>
#include<string>
#include<map>
using namespace std ;

int main()
{
    string a = "hello" ;
    map<string, int> aa ;
    pair<string, int> c,k ;
    c.first = "a";
    c.second = 10 ;
    aa.insert(c) ;
    k.first = "a";
    k.second = 8 ;
    aa.insert(k) ;

    cout << aa.size() <<"----" << aa["a"]<<endl ;
    return 0;
}

