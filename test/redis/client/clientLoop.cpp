#include "clientLoop.h"
//使用gpb命名空间

void clientLoop :: start(string ip, string port) {
    int connFd = client->anetCreateSock() ;
    if(connFd < 0) {
        stop =true ;
    }
    connFd = client->clientConnect(ip, port) ;
    if(connFd < 0) {
        stop = true ;
    }
    //处理命令
    while(!stop) {
        string cmd, res; 
        cout << "myRedis>>" << endl ;
        getline(cin, cmd) ;
        
        //解析命令
        cmdStl = split(cmd, " ") ;
        if(cmdStl.size() == 0) {
            continue ;
        }
        serializeToString(cmdStl, &res) ;
      //  processMsg(command, res) ; 
        //处理序列化的消息
        //发给服务器 
        sendRequest(res) ;
    }
}

//向服务器发送请求
int clientLoop :: sendRequest(string& res) {
    int ret = 0;
    int len = res.size() ;
    if(len < 65535) {
        //设置最后一个元素为１，表示已经发送完成
        res+='1' ;
        char buff[65535] ;
        strcpy(buff, res.c_str()) ;
        ret = writen(connFd, buff, sizeof(buff)) ;  
        if(ret < 0) {
            cout << __FILE__ << "     " << __LINE__ << endl ;
            return  -1 ;
        }
    }
    /*
    //要是消息长度大于65535
    else {
        //设置最后一个元素为０，表示没发完
        char buff[65535] ;  
        int pos = 0 ;
        while(len <= 0) {
            if(len < 65535) {

            }
            strcpy(buff, res.substr(pos, pos+65535).c_str()) ;
            ret = writen(connFd, buff, sizeof(buff)) ;
            if(ret < 0) {
                cout << __FILE__ <<"       "<< __LINE__ << endl ;
                return -1 ;
            }
            pos+=65535 ;
            len-=ret ;
        } 
    }*/
    return ret ;
}

int clientLoop :: processMsg(Command& cmd, string& res) {
    int ret = 0 ;
    //第一个是命令
    //第二个是key
    //第三个是value
    int len = cmdStl.size() ;
    if(len < 3) {
        return -1 ;
    }
    //第一个是命令
    cmd.set_cmd(cmdStl[0]) ;
    //第二个是key
    cmd.set_key(cmdStl[1]) ;
    //设置值
    Value* val = cmd.add_vals() ;
    
    //设置值,值可能重复
    for(int i=2; i<len; i++) {
        string* a = val->add_val() ;
        *a = cmdStl[i] ;
    }
    //将设置好的结果序列化成string
    cmd.SerializeToString(&res) ;
    return ret ;
}
