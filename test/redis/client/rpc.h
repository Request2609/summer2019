#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include "clientLoop.h"
#include "msg.pb.h"

using namespace Messages ;
using namespace std ;

class rpc {
    typedef function<int(int fd, vector<string>&ls)> call ;
    typedef function<Response(string*)> parse ;
public:
    rpc() ;
    ~rpc() ;
public :
    Response getParseString(string* buff) ;
    //设置相应的callMethod方法
    void setCallMethod(call cb) ;
    //反序列化函数
    void setCallMethod(parse par) ; 
    //ip和端口
    void setAddress(string ip, string port) { ipPort.first = ip;  ipPort.second = port ;}
    int sendRequest(vector<string>&argStl) ;
    int Connect() ;
private :
    clientSock client ;
    int conFd ;
    pair<string, string> ipPort ;
    shared_ptr<Command>cmd ;
    call request ;
    //反序列化函数
    parse parseMethod ;
};

