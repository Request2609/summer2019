#include "cmdProcess.h"
//处理消息
int cmdProcess :: processMsg(shared_ptr<aeEvent>&tmp) {
    buffer* bf = tmp->getBuf() ;
    string* buff = bf->getBuf() ;
    Command cmd = parseString(*buff) ;
    //对照命令表
    string key = cmd.key() ;
}
