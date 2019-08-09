#include <iostream>
#include <vector>
using namespace std ;

int main()
{
    vector<int>a ;
    while(1) {
        int n ;
        cin >> n ;
        if(n == -1) {
            break ;
        }
        a.push_back(n) ;
    }
    cout << a.capacity() << endl;
    cout << a.size() << endl ;
    a.shrink_to_fit() ;
    cout << a.capacity() << endl ;
    cout << a.size() << endl ;
}

