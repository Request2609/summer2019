#include "aeEventloop.h"

//初始化事件
//创建epoll句柄等工作
aeEventloop :: aeEventloop() {
    maxFd = -1 ;
    setSize = -1 ;
    stop = false ;
    //创建一个epoll对象
    aep = make_shared<aeEpoll>() ;
    aep->epCreate(SIZE) ;
    apiData = NULL ;
}

//添加监听套接字，及注册相应的读回调函数
int aeEventloop :: addServerEvent(string port, string addr) {
    //将相应套接字加入到epoll中
    shared_ptr<aeEvent> ae  = make_shared<aeEvent>() ; 
    //先获取套接字对象
    aeSocket *aeSock = ae->getSocket() ;  
    //创建套接字对象
    int servFd = aeSock->anetCreateSocket() ;
    //绑定端口地址并进行监听
    aeSock->tcpServer(port.c_str(), addr.c_str(), 20) ;
    //设置非阻塞
    aeSock->setNoBlocking(servFd) ;
    //将该描述符加入到epoll中
    int ret = aep->add(servFd, EPOLLIN) ;
    if(ret < 0) {
        return -1 ;
    }
    //接收套接字的回调函数
    auto func = bind(&aeSocket::acceptClient, aeSock) ;
    //设置服务端读回调函数
    ae->setReadCallBack(func) ;
    //将事件加入到map中
    eventData[servFd] = ae ;
    return 1 ;
}   

//开始监听事件
int aeEventloop :: start() {
    while(true) {
        int ret = aep->wait(fireList) ;
        if(ret < 0) {
            return -1 ;
        }
        
    }
    return 1 ;
}
//设置回调函数
void aeEventloop :: setCallBack(callBack readCb, callBack writeCb) {
    //设置callback函数
    
}
aeEventloop :: ~aeEventloop() {
    
}
