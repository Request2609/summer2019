#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
using namespace std ;
long arr[1000][1000] ;
long cols[1000] ;
long rows[1000] ;

int main()
{
    memset(cols, 1, sizeof(cols)) ;
    memset(rows, 1, sizeof(rows)) ;
    int row, col ;
    cin >> row ;
    cin >> col ;
    for(int i=1; i<=col; i++) {
        cols[i] = 1 ;
    }

    for(int i=1; i<=row; i++) {
        rows[i] = 1 ;
    }

    for(int i=1; i<=row; i++) {
        for(int j=1; j<=col; j++) {
            cin >> arr[i][j] ;
            cols[j]*= arr[i][j] ;
            rows[i]*= arr[i][j] ;
        }
    }
    long maxs = -1 ;
    for(int i=1; i<= row; i++) {
        for(int j=1; j<=col; j++) {
            long c = cols[j]*rows[i]/pow(arr[i][j],2) ;
            maxs = c>maxs ?c :maxs ;
            cout << maxs << "  " ;
        }
        cout << endl ;
    }
    cout << maxs << endl ;
    //计算每一列的乘积
    return 0;
}

