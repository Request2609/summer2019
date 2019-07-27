#include "Process.h"

//获取请求头
int process :: requestHeader(channel* chl) {
    Buffer* bf =chl->getReadBuffer() ;
    //解析请求行
    int readIndex = bf->getReadIndex() ;
    int writeIndex = bf->getWriteIndex() ;
    string a = bf->readBuffer(readIndex, writeIndex) ;
    int end = a.find("\r\n\r\n") ;
    //将信息获取完成，再解析
    //解析请求头
    int index = 0 ;
    while(index != end) {
        string tmp ;
        int e = a.find("\r\n");
        //修改相应的结束标识
        a[e] = '\n' ;
        if(e == end) {
            break ;
        }
        tmp = a.substr(index, e) ;
        index = e+2;
        int ret = getMethod(tmp) ;
        if(ret == GET) {
            return GET ;
        }

        //如果是post请求，找出content_length
        if(ret == POST) {
                  
        }
    }
    return 0  ;  
}   

//获取请求体
int process :: requestBody(channel* channel_) {
    return 1 ;
}

int process :: getMethod(string& line) {
    if(line.find("GET")) {
        return GET ;
    }
    if(line.find("POST")) {
        
    }

}   
