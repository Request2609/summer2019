#pragma once
#include <string>
#include <functional>
#include <map>
#include <vector>
#include "redisDb.h"
#include "aeEvent.h"
#include "msg.pb.h"
#include "cmd.h"

using namespace std  ;
using namespace Messages ;

enum {
    NOTFOUND =   1,
    FOUND = 2,
    KEYINVALID = 3,
    SUCESS = 4,
    PROCESSERROR = -1 
} ; 
//暂时没用
typedef int *redisGetKeysProc();
class cmdSet ;
class redisDb ;
class dbObject ;
class factory ;

class redisCommand {
    //该命令的的处理函数
    typedef function<int(weak_ptr<redisDb>, shared_ptr<Command>)>call ;
public :
    redisCommand(string name, int arity, char* flag, call*callBack, 
                 int fir, int last, int keyStep, long long msecond, long long calls) {
            this->name = name ;
            this->arity = arity ;
            this->flags = flag ;
            this->callBack = callBack ;
            this->getKeys = NULL ;
            this->firstKey = fir ;
            this->lastKey = last ;
            this->keyStep = keyStep ;
            this->microSecond = msecond ;
            this->calls = calls ;
    } 
    ~redisCommand() {}
public :
    int cmdSet() ;
    //函数指针，指向命令的具体实现
  //  string redisCommandProc(shared_ptr<Command>cd) ;
private :
    call* callBack ;
    string stringRes ;
    string name ;
    //参数数量限制,用于验证参数是否正确
    int arity ;
    //命令的权限位，只读的r，不确定的输出R，在redis加载数据的时候使用l
    string flags ;
    //只有在你要用复杂的逻辑去告诉Redis哪个参数才是真正的key的时候才需要。
    redisGetKeysProc*getKeys ;
    //命令的度量项，有数据库设置，初始化为０
    int firstKey ;
    int lastKey ;
    int keyStep ;
    //微妙,时间
    long long microSecond, calls ;
} ;

//命令集合
class cmdSet {
public:
    //设置命令的回调函数
    cmdSet() {
        //申请16个数据库
        dbLs.reserve(16) ;
        //get命令,F表示时间复杂度比较小的命令,Fast
        cmdList.insert(make_pair("get", 
                                 make_shared<redisCommand>("get", 2, "rF", nullptr, 1, 1, 1, 0, 0))) ;
        cmdList.insert(make_pair("set", 
                                 make_shared<redisCommand>("set", -3, "wm", setCmd, 1,1, 1, 0, 0))) ;
        cmdList.insert(make_pair("append", 
                                 make_shared<redisCommand>("append", 3, "wm", NULL, 1,1, 1, 0, 0))) ;
        cmdList.insert(make_pair("hset", 
                                 make_shared<redisCommand>("hset", -4, "wmF", NULL, 1, 1, 1, 0, 0))) ;
        cmdList.insert(make_pair("hget", 
                                 make_shared<redisCommand>("hget", 3, "rF", NULL, 1, 1, 1, 0, 0))) ;
        cmdList.insert(make_pair("hdel", 
                                 make_shared<redisCommand>("hdel", -3, "wF", NULL, 1, 1, 1, 0, 0))) ;
        cmdList.insert(make_pair("del", 
                                 make_shared<redisCommand>("del", -2, "w", NULL, 1, -1, 1, 0, 0))) ;
    }
    ~cmdSet() {}
public :
    int redisCommandProc(int num, shared_ptr<Command>& wcmd) ;
    shared_ptr<redisDb> getDB(int num) ;
    //扩大数据库
    //返回命令集合
    int findCmd(string cmd) ;  
public :
    static int isKeyExist(shared_ptr<redisDb>&wcmd, shared_ptr<Command>&cmd) ;
    static int setCmd(shared_ptr<redisDb>&wcmd, shared_ptr<Command>&tmp) ;
private:
    //数据库,键值是数据库编号码,之后数据库对象
    vector<pair<int, shared_ptr<redisDb>>>dbLs ;
    //命令名称，命令类型
    map<string, shared_ptr<redisCommand>> cmdList ;  
};

