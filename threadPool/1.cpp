#include <iostream>
using namespace std ;

void swap(int &a, int& b) {
	int tmp = std::move(a) ;
	a = std::move(b) ;
	b = std::move(tmp) ;
}

int main()
{
    int&& a = 2 ;
    int b = 3 ; 
    int&& c = std::move(b) ;
    cout << c << endl ;
    cout << a << endl ;
    cout << a << "     " << b << endl ;
    swap(a,b) ;
    cout << a << "   " << b << endl;
    return 0;
}

