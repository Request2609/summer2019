#pragma once
#include <map>
#include <memory>   
#include <string>
#include "cmdSet.h"
#include "aeEvent.h"
#include "buffer.h"
#include "serializeParse.h"

using namespace std ;
//处理消息请求的函数
class cmdProcess {
public :
    //创建消息处理
    cmdProcess() {
        cmdSet_ = make_shared<cmdSet>() ;
    }
    ~cmdProcess() {}
public :    
    int processMsg(shared_ptr<aeEvent>&tmp) ;
    
private :
    //命令集
    shared_ptr<cmdSet> cmdSet_ ;
};

