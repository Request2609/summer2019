#include"sendInfo.h"
#include"sockFd.h"
#include"recvInfo.h"
#include<map>
#include<thread>
#include<signal.h>
using namespace std ;

int main(int argc, const char *argv[])
{

    if (argc != 2)
    {
        printf("usage:%s device_name\n", argv[0]);
        exit(1);
    }
 
    SockFd sfd ;
    //创建原始套接字
    sfd.createPreSock() ;
    
    map<string, string>ipMac ;
    SockFd sock ; 
    int preSock = sock.createPreSock() ;
    if(preSock < 0) {
        exit(1) ;
    }
    RecvInfo re ;
    char ipList[256][128] ;
    //获取相同局域网下的ip列表
    getIpList(preSock, argv[1], ipList) ;

    thread t(sendRequest, preSock, ipList, argv[1]) ;
    re.recvMsg(preSock);

    t.join() ;
    return 0;
}



