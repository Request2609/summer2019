#include "request.h"
///////////////////
void request :: sendAfterParse(int fd, Command& cmd) { 
    string a ;
    //序列化的结果
    cmd.SerializeToArray(&a) ;
    int len = a.size() ;
    if(send(fd, a.c_str(), len+1, 0) < 0) {
        cout << "errno connect" << endl ;
        return ;
    }
}

//匹配键值对
int request :: processCmd(vector<string>&res, Command&com) {
    if(res[0] == "set") {
        //获取该命令的参数个数
        int ret =  cmds::cmdList[res[0]] ;
        if((int)res.size() != ret) {
            cout << "error usage" << endl ;        
            return -1 ;
        }
        com.set_cmd(res[0]) ;
        Key* key = com.add_keys() ;
        string* k = key->add_key() ;
        *k = res[1] ;
        Value* val = com.add_vals() ;
        string* v = val->add_val() ;
        *v = res[2] ;
        return 1 ;
    } 
    else {
        cout << "command not found" << endl ;
        return -1 ;
    }
}

void request :: sendRequest(int fd, vector<string>&res) {
    Command cmd ;
    auto ret = cmds ::cmdList.find(res[0]) ;
    //没找到命令
    if(ret == cmds::cmdList.end()) {
        cout << "command not found!"<< endl ;  
        return ;
    }
    else {
        //从第一个数据
        int r = processCmd(res, cmd) ;
        if(r < 0) {
            return ;
        }
        //序列化,并发送给服务器
        sendAfterParse(fd, cmd) ;
    }
}

