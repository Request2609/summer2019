#include <iostream>
#include <string.h>
using namespace std ;

void test(string text) {
    char* p  = strpbrk(text.c_str(), " \t") ;
    if(!p) {
        cout << "没找到！" <<endl ;
        return ;
    }
    *p = '\0' ;
    char* method = text ;

}

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

