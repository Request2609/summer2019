#include <iostream>
#include<signal.h>
#include<functional>
#include "TcpServer.h"
#include "EventLoop.h"
#include "Channel.h"
#include "Process.h"
#include "Create.h"
using namespace std ;

void onRead(channel* chl) {
    //将信息获取完成，再解析
    //解析请求头
    process pro ;
    int flag = chl->getReadBuffer()->getCanProcess() ;
    if(flag == 1) {
        flag =  pro.requestHeader(chl) ;    
    }
    //上面的程序执行完，可以将flag 置为1，继续解析请求体
    if(flag == 0) {
        
    }
    flag =  0 ;
}

void handle(int signo) {
    return ;
}

int main(int argc, char** argv) {
    //切换到资源目录
    int ret =  chdir("source1") ;
    signal(SIGINT, handle) ;
    if(ret < 0) {
        cout << __FILE__ << "      " << __LINE__ << endl ;
        return 0 ;
    }
    if(argc >3){
        cout << "usage error" << endl ;
        return 0;
    }
    
    eventLoop loop ;
    tcpServer server ;
    connection conn ;
    if(argc == 1) {
        server.create(&loop, "8888") ;
        conn.createSock() ;
        conn.createChannel() ;
    }
    else if(argc == 2) {
        server.create(&loop, argv[1]) ;
        conn.createSock() ;
        conn.createChannel() ;
    }

    if(conn.getSock() == nullptr) {
        cout <<  "haidhohd " << endl ;
    }
    if(argc == 3) {
        server.create(&loop) ;
        conn.setConf(argv[1], argv[2]) ;
    }
    
    //设置新连接的回调函数
    conn.setReadCallBack(std::bind(onRead, placeholders::_1)) ;
    //将新建的连接加入到loop中
    server.addNewConnection(&conn) ;
    //服务器开始工作
    server.start() ;
    //开始等待事件
    loop.loop() ;
    return 0;
}

