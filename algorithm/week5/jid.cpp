#include <iostream>
#include <set>
using namespace std  ;
int a[30] ;
    
int n ;
set<set<int>>ss ;

void dfs(int sum, int pos, set<int>s) {
    if(pos == n+1) return ;
    if(sum == 0) {
       ss.insert(s)  ;
       return ;
    }
    dfs(sum, pos+1, s) ;
    s.insert(a[pos]) ;
    dfs(sum+a[pos], pos+1, s) ;
}

int main()
{
    int n ;
    cin >>n ;
    for(int i=0; i<n; i++) {
        cin >>a[i] ;
    }
    set<int>s ;
    dfs(0, 0, s) ;
    cout << ss.size() << endl ;
    return 0;
}

