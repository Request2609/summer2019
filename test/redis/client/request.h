#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <memory>
#include "msg.pb.h"
#include "cmds.h"
using namespace std ;
using namespace Messages ;
class request ;

class request {
public :
    void sendRequest(int fd, vector<string>&res) ;
    int processCmd(vector<string>&res, Command&com) ;
    void sendAfterParse(int fd, Command& cmd) ;
} ;
