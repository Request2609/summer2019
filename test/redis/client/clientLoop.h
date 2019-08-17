#pragma once
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <functional>
#include <memory>
#include "stringOperation.h"
#include "readWrite.h"
#include "clientSock.h"
#include "aeEpoll.h"
#include "buffer.h"
#include "serializeString.h"

using namespace Messages ;
using namespace std ;
using namespace placeholders ;

class clientLoop {
public:
    clientLoop():stop(false) { 
        client = make_shared<clientSock>() ;
        //申请epoll
    //    aep = make_shared<aeEpoll>() ;
    }
    ~clientLoop() {}
public : 
    void start(string ip, string port) ;
    int processMsg(Command& cmd, string& res) ;
    int sendRequest(string& res) ;
    int setEndSig() ;
private:
  //  shared_ptr<aeEpoll>aep ;
    bool stop ;
    shared_ptr<clientSock> client;
    buffer bf ;
    vector<string> cmdStl ;
    int servFd ;
};

