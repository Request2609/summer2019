#include <iostream>
#include<vector>
#include<algorithm>
using namespace std ;

int main()
{
    //纸牌数组
    int n = 0 ;
    cin >> n ;
    vector<int> arr ;
    for(int i=0; i<n; i++) {
        int m ;
        cin >> m ;
        arr.push_back(m) ;
    }   
    int sum = 0 ;
    //给数组从大到小排序
    sort(arr.rbegin(), arr.rend()) ;
    
    int niu , yang;
    int flag = 0 ;
    for(int i=0; i<n ;i+=2) {	
	//轮到最后一个值了，判断纸牌数目要是奇数的话，将最后一个纸牌直接加入到sum中
        flag = 0 ;
        niu = arr[i]  ;
        if(i+1<n) {
            flag = 1 ;
            yang = arr[i+1] ;
        }
        if(flag == 1)
        sum += niu - yang ;
    }
    
    if(n%2 == 1) {
        sum+=niu ;
    }
    cout <<  sum << endl ;
    return 0;
}

