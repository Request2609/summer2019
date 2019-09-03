#include "rpc.h"

//处理结果，并返回相应的结果
Response rpc :: getParseString(string* buff) {
    //在消息处理处，反序列化
    auto res = parseMethod(buff) ;
    return res ;
}

rpc :: rpc() {
    cmd = make_shared<Command>() ;
}

rpc :: ~rpc() {

}

void rpc :: setCallMethod(call cb) { 
    request = move(cb); 
}   

void rpc :: setCallMethod(parse par) {
    parseMethod = move(par) ;
}

//连接服务器
int rpc :: Connect() {
    int ret = client.anetCreateSock() ;
    cout << "客户端套接字！" << ret << endl ;
    conFd = client.clientConnect(ipPort.first, ipPort.second) ;
    if(conFd < 0) {
        return -1 ;
    }
    cout << "连接－－－－》" << conFd << endl ;
    return conFd ;
}

int rpc :: sendRequest(vector<string>&argStl) { 
    int count = 0 ;
    cout <<  "创建套接字成功!" << conFd << endl ;
    int ret = request(conFd, argStl) ; 
    //断开连接
    if(ret == 5) {
        while(count < 5) {
            conFd = Connect() ;
            if(ret < 0) {
                count ++ ;
                return 5 ;
            }
            else {
                break ;
            }
        }
    }
    ret = request(conFd, argStl) ;
    if(ret < 0) {
        return -1 ;
    }
}
