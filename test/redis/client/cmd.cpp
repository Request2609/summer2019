#include "cmd.h"
//创建命令表
void cmds :: build() {
    cmdList.insert(make_pair("set", 2)) ;
    cmdList.insert(make_pair("get", 2)) ;
}
