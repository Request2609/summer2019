#include "aeEvent.h"
#include "serializeParse.h"

int aeEvent :: processRead() { 
    //读取数据
    char buff[SIZE] ;
    int ret = read(connFd, buff, sizeof(buff)) ;
    if(ret < 0) {
        cout << __FILE__  << "      " << connFd << "      "  << __LINE__ << "                " << strerror(errno) << endl ;
        return -1 ;
    }
    if(ret == 0) {
    }
    //根据返回值，将数据读到buf
    for(int i=0; i<ret; i++) {
        buf.append(buff[i]) ;
    }
    string* aa = buf.getBuf() ;
    int k = aa->size()-1 ;
    if((*aa)[k] != '0') {
        (*aa)[k] = '\0' ;
        ret = readFunc(shared_from_this()) ;
    }
    //先存入缓冲区
    //判断收到结束标志调用回调函数  <接口>预留  
}


int aeEvent :: processWrite() {
    int ret = 0 ; 
 //   int ret =  writeFunc() ; 
    return ret ;
}
