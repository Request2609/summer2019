#include "cmd.h"
#include "clientLoop.h"
#include "method.h"

using namespace std ;

int main(int argc, char** argv) {
    
    //初始化命令表
    cmds::build() ;
    rpc rc ;
    if(argc != 3) {
        cout << __FILE__ << "        " << __LINE__ << endl ;
        return 1 ;
    }
    clientLoop clp ;
    clp.start(argv[1], argv[2]) ;
    return 0;
}

