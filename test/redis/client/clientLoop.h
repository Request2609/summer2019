#pragma once
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <memory>
#include "readWrite.h"
#include "clientSock.h"
#include "buffer.h"
#include "stringOperation.h"
#include "serializeString.h"

using namespace Messages ;
using namespace std ;

class clientLoop {
public:
    clientLoop():stop(false) { client = make_shared<clientSock>() ;}
    ~clientLoop() {}
public : 
    void start(string ip, string port) ;
    int processMsg(Command& cmd, string& res) ;
    int sendRequest(string& res) ;
private:
    bool stop ;
    shared_ptr<clientSock> client;
    buffer bf ;
    vector<string> cmdStl ;
    int connFd ;
};

