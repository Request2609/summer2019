#include <iostream>
#include <signal.h>
#include "Process.h"
#include "Channel.h"
#include "Server.h"

using namespace std ;

int fd  ;
//消息处理函数
void onMessage(channel chl) {
    //将消息全部读取出来
    //消息处理函数将get请求处理完成触发写事件，
    //向另一端发送消息，通知写结束
    logBuf* buf = chl.getBuf() ;
    cout <<"\nflag:" << buf->flag << "\n姓名:"<<buf->name <<"密码:" << buf->password << endl ;
    cout <<"服务类型：" << buf->type << "套接字"<< chl.getConnFd()<< endl ;
    cout << "请求路径："<< buf->path_ << std::endl ;
    cout << "请求版本："<< buf->version << std::endl ;
    //发送资源
    server serv(&chl) ;
    serv.process() ;
}

void deal(int sig) {
    close(fd) ;
}
    
int main()
{
    chdir("../www") ;
    epOperation ep ;
    process pro(10, &ep) ;
    fd = pro.getFd() ;
   // pro.createEpoll() ;
    
    signal(SIGINT, deal) ;
    signal(SIGPIPE, deal) ;
    //设置消息回调
    pro.setReadCallBack(std::bind(onMessage, std::placeholders::_1)) ;
    pro.start() ;

    //加入到epoll中
    return 0;
}

