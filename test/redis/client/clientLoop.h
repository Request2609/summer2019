#pragma once
#include <iostream>
#include <memory>
#include "buffer.h"
#include "clientSock.h"

using namespace std ;

class clientLoop {
public:
    clientLoop():stop(false) { client = make_shared<clientSock>() ;}
    ~clientLoop() {}
public : 
    void start(string ip, string port) ;
private:
    bool stop ;
    shared_ptr<clientSock> client;
    buffer bf ;
};

