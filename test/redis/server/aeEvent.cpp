#include "aeEvent.h"

int aeEvent :: processRead() { 
    //读取数据
    char buf[65535] ;
    int ret = read(connFd, buf, sizeof(buf)) ;
    if(ret < 0) {
        cout << __FILE__ << "      "  << __LINE__ << endl ;
        return -1 ;
    }
    int flag = 0 ;
    //先存入缓冲区
    //判断收到结束标志调用回调函数  <接口>预留  
    if(flag == 1) 
    ret = readFunc(shared_from_this()) ;
    return ret ;
}


int aeEvent :: processWrite() {
    int ret = 0 ; 
 //   int ret =  writeFunc() ; 
    return ret ;
}
