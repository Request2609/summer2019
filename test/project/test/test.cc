#include <iostream>
#include <memory>
#include<functional>
using namespace std ;
int main()
{
    string a ;
    a = "hello world!" ;
    a = a.substr(1, a.length()-1) ;
    cout << a << endl ;
    cout <<a.find(" ") << endl ;
}

