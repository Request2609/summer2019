#ifndef _PROCESS_H_
#define _PROCESS_H_
#include<iostream>
#include<string>
#include"Channel.h"
using namespace std ;
enum {
    GET = 1, POST
} ;

class process
{
public:
    process():paths(""), method(-1), version("") {}
    ~process() {}
public :
    int requestHeader(channel* channel_) ;
    int requestBody(channel* channel_) ;
    int getMethod(string& line) ;
private:
    string post ;
    string paths ;
    int method ;
    string version ;
};
#endif
