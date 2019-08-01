#ifndef _PROCESS_H_
#define _PROCESS_H_
#include<iostream>
#include<string>
#include<sys/stat.h>
#include"Channel.h"
#include"ReadWrite.h"
#include "Socket.h"
#define BUFLEN 65535 

using namespace std ;
enum {
    GET = 1, POST, DEFAULT
} ;

enum {
    NOT_FOUND=404, OK=200
} ;

//向进程发送的登录信息
struct logBuf {
    //暂时业务为登录
    int flag ;
    int type ;
    char name[512] ;
    char password[512] ;
    char version[1024] ;
    char path_[1024] ;
} ;

class process
{
public:
    process():paths(""), method(-1), version("") {}
    ~process() {}
public :
    int isExist() ;
    int requestHeader(channel* channel_) ;
    int requestBody(channel* channel_) ;
    int getMethod(string& line) ;
    int messageSend(const string& tmp, channel*chl) ;
    int getVersionPath(string  tmp) ;
    void responseHead(channel* chl, string type, long len, int statusCode, string tip) ;
    void readFile(const char* file, channel* chl) ;
    void sendNotFind(channel* chl) ;
    void readFile(channel* chl) ;
    int sendFile(channel*chl) ;
    string getFileType() ;
    int processArgGet(string tmp, channel* chl) ;
    int getContentLength(string a, channel* chl) ;  
    int getSubmitInfo(string& info, int pos, int l, string& a, channel* chl) ;
    int doPost(channel* chl, string& info) ;
    int sendSock(logBuf& buf, int fd, int connFd) ;
private :
    string post ;
    string paths ;
    int method ;
    string version ;
};
#endif
