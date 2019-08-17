#include "aeEventloop.h"
#include "aeEvent.h"
#include "cmdProcess.h"

int readOnMessage(shared_ptr<aeEvent>tmp) { 
    //处理事件    
    cmdProcess cmdPro ;
    cmdPro.processMsg(tmp) ;
  /*  buffer* bf = tmp->getBuf() ;
    string* buf = bf->getBuf() ;
    Command cmd = parseString(*buf) ;
    //最后一定得清空改用的读缓冲区
    buf->clear() ;
    */
    return 1 ;
}

int main(int argc, char** argv) {

    if(argc != 3) {
        cout << "usage:<./a.out><ip><port>" << endl ;
        return 1 ;
    }
    aeEventloop aeLoop ;
    //设置读回调函数
    aeLoop.setReadCallBack(readOnMessage) ;
    aeLoop.addServerEvent(argv[1], argv[2]) ;
    aeLoop.start() ;
    return 0;
}

