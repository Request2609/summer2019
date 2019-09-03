#include <iostream>
#include <vector>
#include <memory>
using namespace std ;

void func2(vector<int>&ls, int& i) {
    ls.push_back(i) ;
}

void func(vector<shared_ptr<int>>&ls) {
    int i = 10 ;
    ls.push_back(shared_ptr<int>(new int(i))) ;
    
}

int main()
{
    vector<shared_ptr<int>>ls ;
    func(ls) ;
    for(int i=0; i<ls.size(); i++) {
        cout << *ls[i] << endl;
    }
}

