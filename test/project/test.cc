#include <iostream>
#include <memory>
#include<functional>
using namespace std ;
int main()
{   
    function<void()> func=nullptr;
    if(func ==nullptr) {
        cout << "hello" << endl ;
    }
    std::cout << "Hello world" << std::endl;
    return 0;
}

