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
public:
    rpc() {}
    ~rpc() {}
public :
    //设置相应的callMethod方法
    void setCallMethod(call cb) { callMethod = move(cb); }   
   
private :
    shared_ptr<Command>cmd ;
    call callMethod ;
};

