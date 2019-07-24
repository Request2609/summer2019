#include"Buffer.h"
#include"collectErr.h"

Buffer :: Buffer() {
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

