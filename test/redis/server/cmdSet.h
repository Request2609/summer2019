#pragma once
#include <string>
#include <map>
#include <vector>
#include "aeEvent.h"
using namespace std  ;

//暂时没用
typedef int *redisGetKeysProc();

class redisCommand {
public :
    redisCommand(string name, int arity, char* flag, redisGetKeysProc*func, 
                 int fir, int last, int keyStep, long long msecond, long long calls) {
            this->name = name ;
            this->arity = arity ;
            this->flags = flag ;
            this->getKeys = func ;
            this->firstKey = fir ;
            this->lastKey = last ;
            this->keyStep = keyStep ;
            this->microSecond = msecond ;
            this->calls = calls ;
    } 
    
    ~redisCommand() {}
public :
    //函数指针，指向命令的具体实现
    //将客户端信息传进去
    int redisCommandProc(shared_ptr<aeEvent>tmp) ;
public :
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
    cmdSet() {
        //get命令,F表示时间复杂度比较小的命令,Fast
        cmdList.insert(make_pair("get", 
                                 make_shared<redisCommand>("get", 2, "rF", NULL, 1, 1, 1, 0, 0))) ;
        cmdList.insert(make_pair("set", 
                                 make_shared<redisCommand>("set", -3, "wm", NULL, 1,1, 1, 0, 0))) ;
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
    //返回命令集合
    map <string, shared_ptr<redisCommand>>const *getCmdList() {
        return &cmdList ;
    }   
private:
    //命令名称，命令类型
    map<string, shared_ptr<redisCommand>> cmdList ;  
};

