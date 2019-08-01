#include <iostream>
#include <memory>
#include "Channel.h"
#include"Process.h"
int channel :: setConnFd() {
    int cmsghdrlen = CMSG_LEN(sizeof(int)) ;
    logBuf buf ;
    bzero(&buf, sizeof(buf)) ;
    struct iovec iov ;
    struct msghdr msg ;
    //设置套接字数据域
    iov.iov_base = &buf ;
    iov.iov_len = sizeof(buf);
    msg.msg_iov = &iov ;
    msg.msg_iovlen = 1 ;
    msg.msg_name = NULL ;
    msg.msg_namelen = 0 ;
    std::shared_ptr<cmsghdr>cmptr = std::shared_ptr<cmsghdr>(new cmsghdr) ;
    msg.msg_control = &(*cmptr) ;
    msg.msg_controllen = cmsghdrlen ;

    int fd = recvmsg(cliFd, &msg, 0) ;
    if(fd < 0) {
        std::cout << __FILE__ << "     " << __LINE__ << std::endl ;
        return -1 ;
    }
    else {
        logBuf buf = *(logBuf*)msg.msg_iov->iov_base ;
        this->buf = &buf ; 
        connFd = *(int*)CMSG_DATA(&(*cmptr)) ;
        fflush(stdout) ;
        return connFd ;
    }
}
