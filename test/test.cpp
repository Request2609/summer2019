#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>

int recvfd(int);

void client_socketun(){
    int sockfd, newfd, len, nr;
    sockaddr_un un;
    char buf[20]={0};

    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, "/tmp/s");
    len = sizeof(un.sun_family) + strlen(un.sun_path);

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if(connect(sockfd, (sockaddr *)&un, len) == -1){//连接socket
        printf("connect error");
        return ;
    }

    // read(sockfd, buf, 20);
    recv(sockfd, buf, 20, 0);//接收普通数据
    printf("接收到普通数据：%s\n", buf) ; 
    if((newfd = recvfd(sockfd)) == -1){//接收msg数据
        printf("rec error");
    }
    else{
        printf("通过新的文件描述符读取文件数据：\n") ;
        while(1){
            if((nr = read(newfd, buf, 10)) == -1){
                perror("read error");
            }
            if(nr == 0) {
                break ;
            }
            else{
                printf("%s", buf);
                fflush(stdout);
            }
        }
    }
    close(sockfd);
}

struct  A {
    char buf[1024] ;
    int flag = 1 ;
} ;

int recvfd(int sockfd){
    int newfd, nr;
    struct cmsghdr *cmptr = nullptr;//OUT
    int cmsghdrlen = CMSG_LEN(sizeof(int));
    struct iovec iov;
    struct msghdr msg;
    A a ;
    bzero(&a, sizeof(a)) ;
    iov.iov_base = &a;
    iov.iov_len = sizeof(a);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    
    cmptr = (cmsghdr *)malloc(cmsghdrlen);
    msg.msg_control = cmptr;
    msg.msg_controllen = cmsghdrlen;

    if((nr = recvmsg(sockfd, &msg, 0)) < 0){
        perror("recvmsg error\n");
    }else{
        A a = *(A*)msg.msg_iov->iov_base ;
        printf("A中的内部数据：%d-----(%s)\n", a.flag, a.buf) ;
        newfd = *(int *)CMSG_DATA(cmptr);
        fflush(stdout);
        return newfd;
    }
    
    return -1;
}

int main(){

    client_socketun();

    return 0;
}

