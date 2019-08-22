#pragma once
#include "cmd.h"
#include <iostream>
#include <vector>
#include <memory>
#include "msg.pb.h"
using namespace std ;
using namespace Messages ;

void sendRequest(int fd, vector<string>&res) {
    Command cmd ;
    auto ret = cmds ::cmdList.find(res[0]) ;
    //没找到命令
    if(ret == cmds::cmdList.end()) {
        cout << "command not found!"<< endl ;  
    }
    else {
        //从第一个数据
        processCmd(res, Command&cmd) ;
    }
}

int processCmd(vector<string>&res, Command&com) {
    if(res[0] == "set") {
        int ret =  cmds::cmdList[res[0]] ;
        if((int)res.size() != ret) {
                       
        }
    } 
}
