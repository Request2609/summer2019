#include "Buffer.h"

char buffer :: operator[](int i) {
    if(i > (int)info.size()) {
        return '\0' ;
    }
    else {
        return info[i] ;
    }
}


