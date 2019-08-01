#include <iostream>
#include <vector>
int main()
{
    std::vector<int> ls ;
    int len = 10 ;
    while(len--) {
        ls.push_back(len) ;
    }
    int  i =0  ;
    while(ls.size()) {
        std:: cout << ls[i] <<"--------->" <<(int)ls.size()<<std:: endl ;
        i++ ;
        ls.pop_back() ;
    }
    return 0;
}

