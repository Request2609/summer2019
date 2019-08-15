#include "clientLoop.h"

void clientLoop :: start(string ip, string port) {
    int connFd = client->anetCreateSock() ;
    if(connFd < 0) {
        stop =true ;
    }
    int ret = client->clientConnect(ip, port) ;
    if(ret < 0) {
        stop = true ;
    }
    //处理事件
    while(!stop) {
        string command ;
        cout << "myRedis>>" << endl ;
        cin >> command ;
    }
}
