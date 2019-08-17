#pragma once
#include <string>
#include <map>
#include <vector>
using namespace std  ;

//命令集合
class cmdSet {
public:
    cmdSet() {
        //get命令
        cmdList.insert(make_pair("get", "getcmd")) ;
        //set 命令
        cmdList.insert(make_pair("set", "setcmd")) ;
        cmdList.insert(make_pair("append", "appendcmd")) ;
        //哈希命令
        cmdList.insert(make_pair("hget", "hgetcmd")) ;
        cmdList.insert(make_pair("hset", "hsetcmd")) ;
        cmdList.insert(make_pair("hdel", "getcmd")) ;
        /*
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        cmdList.insert(make_pair("get", "getcmd")) ;
        */
    }
    ~cmdSet() {}
public :
    //返回命令集合
    map <string, string>const *getCmdList() {
        return &cmdList ;
    }   
private:
    //命令名称，命令类型
    map<string, string> cmdList ;  
};

