#include "clientLoop.h"
using namespace std ;

int main(int argc, char** argv) {
    
    if(argc != 3) {
        cout << __FILE__ << "        " << __LINE__ << endl ;
        return 1 ;
    }
    clientLoop clp ;
    clp.start(argv[1], argv[2]) ;
    return 0;
}

