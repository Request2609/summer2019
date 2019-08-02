#pragma once
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Channel.h"
#include "Buffer.h"
#include "Process.h"
#include "ReadWrite.h"
#define SIZE 65535

enum {
    NOTFOUND=404, OK= 200
} ;

class server {
public:
    server(channel* chl) {
        this->chl = chl ;
        //获取Unix用于套接字数据包
        buf = chl->getBuf() ;
    }
    ~server() {}
public :
    void responseHead(std::string type, long len, int statusCode, std::string tip) ;
    std::string  getFileType(std::string file) ;
    void process() ;
    int logIn() ;
    int sendHtml() ;
    void sendNotFind() ;
    void readFile(const char* name) ;
    int sendToBrower() ;
private:
    buffer buffer_ ;   
    logBuf *buf ;
    channel * chl ;
};

