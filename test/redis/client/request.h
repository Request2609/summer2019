#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <memory>
#include "msg.pb.h"
#include "cmds.h"

//class request ;
using namespace std ;
using namespace Messages ;

class request {
public :
    static void sendRequest(int fd, vector<string>&res) ;
    static int processCmd(vector<string>&res, Command&com) ;
    static void sendAfterParse(int fd, Command& cmd) ;
} ;
