#include <iostream>
#include <signal.h>
#include "Process.h"
#include "Channel.h"
#include "Buffer.h"
using namespace std ;

int fd  ;
//消息处理函数
void onMessage(channel chl) {
    //将消息全部读取出来
    //消息处理函数将get请求处理完成触发写事件，
    //向另一端发送消息，通知写结束
    logBuf* buf = chl.getBuf() ;
    cout <<"\nflag:" << buf->flag << "\n姓名:"<<buf->name <<"密码:" << buf->password << endl ;
    cout <<"服务类型：" << buf->type << endl ;
}

void deal(int sig) {
    close(fd) ;
}
    
int main()
{
    process pro(10) ;
    fd = pro.getFd() ;
    pro.createEpoll() ;
    
    signal(SIGINT, deal) ;
    signal(SIGPIPE, deal) ;
    //设置消息回调
    pro.setReadCallBack(std::bind(onMessage, std::placeholders::_1)) ;
    pro.start() ;

    //加入到epoll中
    return 0;
}

