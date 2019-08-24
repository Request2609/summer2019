#include "backInfo.h"

Response backInfo :: notFind()  {
    res.set_reply("command not found!") ;
    return res ;
}

Response backInfo :: okReply() {
    res.set_reply("OK") ;
    return res ;
}

Response backInfo :: keyInvalid() {
    res.set_reply("key invalid!") ;
    return res ;
}

Response backInfo :: processError() {
    res.set_reply("process error!") ;
    return res ;
}
