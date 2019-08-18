#include "cmdProcess.h"
//处理消息
int cmdProcess :: processMsg(shared_ptr<aeEvent>&tmp) {
    buffer* bf = tmp->getBuf() ;
    string* buff = bf->getBuf() ;
    //反序列化
    Command cmd = parseString(*buff) ;
    //对照命令表
    string co = cmd.cmd() ;
    //键值
    string key = cmd.key() ;    
    //获取key后面的部分
    getAfterKeyPart() ;
    int size = cmd.vals_size() ;
    //获取key以后的部分
    for(int i=0; i<size; i++) {
        Value vals = cmd.vals(i) ;
        int len = vals.val_size() ;
        for(int j=0; j<len; j++) {
            lastKey.push_back(vals.val(j)) ;  
        }
    }
    //findCommand
    int res = findCommand(cmd) ;
    if(res == 0) {
        int ret = sendMsg(tmp) ;   
        if(ret < 0) {
            return -1;
        }
    }
}

int cmdProcess :: sendMsg(shared_ptr<aeEvent>tmp) {
    int fd = tmp->getConnFd() ;
    Command cmd ;
    char buf[SIZE] ;
    cmd.set_status(0) ;
    int ret = write(fd, buf, sizeof(buf)) ;
    if(ret < 0) {
        cout << __FILE__ << "     " << __LINE__ << endl ;
        return -1 ;
    }
    return 1 ;
}

//判断名令存不存在
int cmdProcess:: findCommand(Command& cmd) {
    map<string, shared_ptr<redisCommand>>const* ll = cmdSet_->getCmdList() ;
    auto res = ll->find(cmd.cmd()) ;
    if(res == ll->end()) {
        return 0 ;
    }
    return 1 ;
}

