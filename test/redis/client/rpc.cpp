#include "rpc.h"

//处理结果，并返回相应的结果
shared_ptr<Command> rpc :: getParseString(string* buff) {
    //在消息处理处，反序列化
    auto res = parseMethod(buff) ;
    return res ;
}

rpc :: rpc() {
    cmd = make_shared<Command>() ;
}

rpc :: ~rpc() {

}

void rpc :: setCallMethod(call cb) { 
    request = move(cb); 
}   

void rpc :: setCallMethod(parse par) {
    parseMethod = move(par) ;
}
