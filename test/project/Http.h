#ifndef _HTTP_H_
#define _HTTP_H_
#include <iostream>
class http
{
public:
    http() {}
    ~http() {}

private:
    //版本
    std :: string version ;
    //方法
    std :: string method ;
    //路径
    std :: string paths ;
};
#endif
