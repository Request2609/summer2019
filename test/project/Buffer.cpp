#include"Buffer.h"
#include"collectErr.h"

Buffer :: Buffer():flag(0) {
    hasData = -1 ;
    readIndex = 0 ;
    writeIndex = 0 ;
    buffer.clear() ; 
}

Buffer :: Buffer(const char* buf) {
    assert(buf != NULL) ; 
    int len = strlen(buf) ;
    writeIndex = len ;
    for(int i=0; i<len; i++) {
        buffer.push_back(buf[i]) ;
    }
}

Buffer :: Buffer(std::string buf) {
    int len = buf.size() ;
    writeIndex = len ;
    for(int i=0; i<len; i++) {
        buffer.push_back(buf[i]) ;
    }
}

//移动缓冲区中的读指针
int Buffer :: retreiveBuffer(int n) {
    if(readIndex+n >= writeIndex) {
        readIndex = 0 ;
        writeIndex = 0 ;
        buffer.clear() ;
    }  
    else {
        readIndex += n ;
    }
    return readIndex ;
}

//清空用户缓冲区
void Buffer :: bufferClear() {
    readIndex = 0 ;
    writeIndex = 0 ;
    buffer.clear() ;
}

//读取缓冲区，这里注意不会移动readIndex
std :: string Buffer :: readBuffer(int start, int end) {
    std::string a ;
    for(int i=start; i<end; i++) {
        a+=buffer[i] ; 
    }
    return a ;
}

//删除start到end的部分
int Buffer :: retreiveBuffer(int start, int end) {
    //如果读写指针重合，将缓冲区清空
    if(readIndex >= writeIndex) {
        buffer.clear() ;
    }   
    if(start > end) {
        writeErr(__FILE__, __LINE__) ;
        return -1 ;
    }   
    readIndex += (end-start);
    return readIndex ;
}

int Buffer :: readBuffer(int fd) {
    char buffer_[4096] ;
    //接收消息
    int n ;
    if((n = readn(fd, buffer_, sizeof(buffer_))) < 0) {
        writeErr(__FILE__, __LINE__) ;
        return -1 ;
    }
    std::string end ;
    //处理消息
    //将消息传到缓冲区中
    for(int i=0; i<n; i++) {
        //写指针自增
        writeIndex ++ ;
        //设置当前channel对象的缓冲区
        buffer.push_back(buffer_[i]) ;
        //表明这段数据可以进行处理了
        if((buffer_[i] == '\r' || buffer_[i] == '\n') && end !="\r\n\r\n") {
            end += buffer_[i]; 
        }
        //判断
        if(end == "\r\n" && buffer_[i+1] != '\r') {
            end.clear() ;
        }
    }
    //如果收到了最后面的两个"\r\n\r\n"
    //就调用消息处理
    if(end == "\r\n\r\n") {
        flag = true ;     
    }

    if(hasData != -1) {
        hasData-=n ;
        if(hasData == 0) {
            flag = true ;
        }
    }
    //且指针指向的不是０位置，读指针和写指针在同一位置，清空缓冲区
    if((readIndex != 0 && writeIndex!=0) && readIndex == writeIndex) {
        buffer.clear() ;
        readIndex = 0;
        writeIndex = 0 ;
    }
    return n ;
}


