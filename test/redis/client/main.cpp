#include <iostream>
#include "cmds.h"
#include "clientLoop.h"
#include "rpc.h"
#include "request.h"
using namespace std ;

int main(int argc, char** argv) {
    
    //初始化令表
    cmds::build() ;
    rpc rc ;
    if(argc != 3) {
        cout << __FILE__ << "        " << __LINE__ << endl ;
        return 1 ;
    }

    rc.setCallMethod(request :: sendRequest) ;
    clientLoop clp(&rc) ;
    
    clp.start(argv[1], argv[2]) ;
    return 0;
}

