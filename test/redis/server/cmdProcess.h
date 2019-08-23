#pragma once
#include <map>
#include <memory>   
#include <vector>
#include <string>
#include "aeEvent.h"
#include "redisDb.h"
#include "rpc.h"
#include "cmdSet.h"
#include "buffer.h"
#include "serializeParse.h"
#include "readWrite.h"
#include "enum.h"

#define SIZE 4096
using namespace std ;
class rpc ;
class cmdSet ;
class redisCommand ;
//错误类型
enum {
    NOTFOUND = 1,
    FOUND = 2,
    KEYINVALID = 3,
    SUCESS = 4, 
    PROCESSERROR = -1
} ; 

//处理消息请求的函数
class cmdProcess {
public :
    //创建消息处理
    cmdProcess() {
        cmdSet_ = make_shared<cmdSet>() ;
        //获取命令表
        rc = make_shared<rpc>() ;
    }
    ~cmdProcess() {}
public : 
    int processMsg(shared_ptr<aeEvent>&tmp) ;
    int sendMsg(shared_ptr<aeEvent>tmp) ;
    void getAfterKeyPart() ;
    int findCmd(const shared_ptr<Command>tmp) ;
private :
    //命令集
    //键值以后的部分成员
    shared_ptr<cmdSet> cmdSet_ ;
    vector<string> lastKey ;   
    //rpc,主要进行序列化和反序列化
    shared_ptr<rpc> rc ;
};

