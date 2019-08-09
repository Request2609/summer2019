#include <iostream>
using namespace std ;

char a[101][101] ;
int find(int n, int m, string word) {

    int sum = 0 ;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m ; j++) {
            //从四个方向找
            //向当前字符的右边找
            //下面找
            //下45读度角开始找
            int len = word.size() ;
            int count = 3 ;
            while(count--) {
                int p = 1;
                if(count == 2) 
                    for(int l=0; l<len; l++) {
                        int t = i+l ;
                        if(t > n) {
                            break ;
                        }
                        if(a[t][j] != word[l]) {
                            p = 0 ;
                            break ;                   
                        }
                    } 
                if(count == 1) 
                    for(int l=0; l<len; l++) {
                        int t = i+l ;
                        int w = j+l ;
                        if(t>n||w>m) {
                            break ;
                        }
                        if(a[t][w] != word[l]) {
                            p = 0 ;    
                            break ;
                        }
                    }
                if(count == 0) 
                    for(int l=0; l<len; l++) {
                        int w = j+l ;
                        if(w>m) {
                            break ;
                        }
                        if(a[i][w] != word[l]) {
                            p = 0 ;    
                            break ;
                        }
                    }
                if(p == 1) {
                    sum++ ;
                }
            }
        } 
    }
    return sum ;
}

int main() {
    int n, m;
    int num ;
    cin>>num ;
    while(num--) {
        cin >> n ;
        cin >> m ;
        getchar() ;
        for(int i=1; i<=n; i++) {
            for(int j = 1; j<=m; j++) {
                cin>>a[i][j] ;
            }
        }
         string word ;

        cin >> word ;
        int res = find(n, m, word) ;
        cout << res << endl ;
    }
    
    return 0;
}

