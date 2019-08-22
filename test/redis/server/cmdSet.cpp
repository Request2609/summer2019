#include "cmdSet.h"
#include "enum.h"

int cmdSet:: findCmd(string cmd) {
    if(cmdList[cmd].find() == cmdList.end()) {
        return NOTFOUND ;
    }   
    else {
        return FOUND ;
    }
}

shared_ptr<redisDb> cmdSet :: getDB(int num) {
    //数据库为空
    int len = dbLs.size() ;
    for(int i=0; i<len; i++) {
        if(i == num) {
            return dbLs[i] ;
        }
    }
    return nullptr ;
}
int cmdSet :: setCmd(weak_ptr<redisDb>&wcmd, shared_ptr<Command>&cmd) {
    //命令
    int num = cmd->keys_size() ;
    if(num > 1) {
        return -1 ;
    }   
    
}


int cmdSet ::  redisCommandProc(int num, shared_ptr<Command>&wcmd) {
    //数据库编号
    weak_ptr<redisDb> wrdb = getDB(num) ;
    string cmd = wcmd->cmd() ;
    if(cmd == "set") {
        int ret = cmdList[cmd].callBack(wrdb, wcmd) ;
        if()
    }   
}
