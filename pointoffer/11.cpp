#include <iostream>
/*
实现函数 double Power(double base, int exponent)，
求 base 的 exponent 次方。 不得使用库函数，同时不需要考虑大数问题。
 * */
double halfRes(double base, int ex) {
    double result = 1.0 ;
    for(int i=1; i<=ex; i++) {
        result*=base ;
    }
    return result ;
}

double res(double base, int ex) {
    if(base == 0) {
        return 1 ;
    }
    if(ex == 0) {
        return 1 ;
    }
    //折半计算
    double result =  halfRes(base, ex>>1) ;
    result *= result ;
    if((ex&1) == 1) result*=base ;
    return result ;
}

int main()
{
    std::cout << res(2, 6) ; 
    return 0;
}

