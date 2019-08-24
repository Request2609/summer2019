#include "rpc.h"

//处理结果，并返回相应的结果
shared_ptr<Command> rpc :: getParseString(string* buff) {
    //在消息处理处，反序列化
    auto res = parseMethod(buff) ;
    return res ;
}


int rpc :: response(shared_ptr<Response>res, int fd) {
    //回复客户端
    string s ;
    //序列化
    res->SerializeAsString(&s) ;
    //向客户端发送消息
    int ret = send(fd, s.c_str(), s.size(), 0) ;
    if(ret < 0) {
        cout << __FILE__ << "      " << __LINE__ << endl ;
        return -1 ;
    }
    return ret ;
}

