#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <arpa/inet.h>
 #include<netinet/tcp.h>
#include <memory>
#include "msg.pb.h"

using namespace std ;
using namespace Messages ;
class cmds ;
class request {
public :
    static int isConnect(int fd) ;
    static int sendAfterSerial(int fd, Command& cmd) ;
    static int sendReq(int fd, vector<string>&res) ;
    static int processCmd(vector<string>&res, Command&com) ;
} ;

class cmds {
public:
    cmds() ;
    ~cmds() ;
public :
    //一个命令
    map<string, int>cmdList ;
public :
    void build() ;
};

