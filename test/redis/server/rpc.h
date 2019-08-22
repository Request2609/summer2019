#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include "aeEvent.h"
#include "msg.pb.h"

using namespace Messages ;
using namespace std ;

class rpc {
    typedef function<void(shared_ptr<Command>cmd, shared_ptr<aeEvent>event, string& res)> call ;
    typedef function<shared_ptr<Command>(string*)> parse ;
public:
    rpc() {cmd = make_shared<Command>() ;}
    ~rpc() {}
public :
    shared_ptr<Command>getParseString(string* buff) ;
    //设置相应的callMethod方法
    void setCallMethod(call cb) { callMethod = move(cb); }   
    //反序列化函数
    void setCallMethod(parse par) { parseMethod = move(par) ;}
private :
    shared_ptr<Command>cmd ;
    call callMethod ;
    //反序列化函数
    parse parseMethod ;
    
};
