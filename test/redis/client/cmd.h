#pragma once
#include <string>
#include <memory>
#include <map>
using namespace std ;
class cmds ;

class cmds {
public:
    cmds() {
    }
    ~cmds() {}

public :
    static map<string, int>cmdList ;
public :
    static void build() ;
};

