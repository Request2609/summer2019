#include <iostream>
using namespace std ;
void swap(int& i, int& k) {
    int tmp = move(i);
    i= move(k) ;
    k= move(tmp) ;
}
int main()
{
    int k = 1 ;
    int j = 3 ;
    cout << k << j << endl ;
    swap(k, j) ;
    cout << k << j << endl ;
    return 0;
}

