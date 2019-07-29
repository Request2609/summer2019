#ifndef _PROCESS_H_
#define _PROCESS_H_
#include<iostream>
#include<string>
#include<sys/stat.h>
#include"Channel.h"
#include"ReadWrite.h"
using namespace std ;
enum {
    GET = 1, POST, DEFAULT
} ;

enum {
    NOT_FOUND=404, OK=200
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
private:
    string post ;
    string paths ;
    int method ;
    string version ;
};
#endif
