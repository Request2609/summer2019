#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include "msg.pb.h"

using namespace Messages ;
using namespace std ;

class rpc {
    typedef function<void(int fd, vector<string>&ls)> call ;
    typedef function<shared_ptr<Command>(string*)> parse ;
public:
    rpc() ;
    ~rpc() ;
public :
    void sendRequest(int connFd, vector<string>&argStl) { request(connFd, argStl) ; }
    shared_ptr<Command>getParseString(string* buff) ;
    //设置相应的callMethod方法
    void setCallMethod(call cb) ;
    //反序列化函数
    void setCallMethod(parse par) ; 
private :
    
    shared_ptr<Command>cmd ;
    call request ;
    //反序列化函数
    parse parseMethod ;
};

