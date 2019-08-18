#pragma once
#include <map>
#include <memory>   
#include <string>
#include "cmdSet.h"
#include "aeEvent.h"
#include "buffer.h"
#include "serializeParse.h"
#include "readWrite.h"
#define SIZE 4096

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
    int findCommand(Command& cmd) ;
    int sendMsg(shared_ptr<aeEvent>tmp) ;
    getAfterKeyPart() ;
private :
    //命令集
    //键值以后的部分成员
    shared_ptr<cmdSet> cmdSet_ ;
    vector<string> lastKey ;   
};

