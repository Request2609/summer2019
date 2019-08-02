#include "Process.h"

int process :: postRequest(string& tmp, channel* chl, string& bf) {
        int ret = 0 ;
        //获取到请求路径和版本号
        getVersionPath(tmp) ;
        ret = getContentLength(bf, chl) ;
        if(ret == -5) {
            sendNotFind(chl) ;
            return POST ;
        }
        else {
            paths = paths.c_str()+1 ;
            readFile(chl) ;
            flag = 1 ;
            messageSend(tmp, chl) ; 
            return POST ;
        }
    return 1 ;
}

string process :: changeHtml(string& tmp) {
    ::FastCgi fc ;
    string res ;
    fc.setRequestId(1) ;
    fc.startConnect() ;
    fc.sendStartRequestRecord() ;
    return res ;
}

int process :: getRequest(channel* chl, string& tmp) {
        int ret =  tmp.find("?") ;
        //带参数的url，搜索功能
        if(ret != -1) { 
            processArgGet(tmp, chl) ;      
        }
        //要是php的话，就得转成html然后给服务器发
        //有php-fpm完成
        if(tmp.find("php")) {
            string file = changeHtml(tmp) ;
            
        }
        ret = messageSend(tmp, chl) ;
        return 1 ;
}

//获取请求头
int process :: requestHeader(channel* chl) {
    Buffer* bf =chl->getReadBuffer() ;
    //解析请求行
    int readIndex = bf->getReadIndex() ;
    int writeIndex = bf->getWriteIndex() ;
    string a = bf->readBuffer(readIndex, writeIndex) ;
    //将信息获取完成，再解析
    //解析请求头
    int index = 0 ;
    string tmp ;
    int e = a.find("\r\n");
    //修改相应的结束标识
    a[e] = '\n' ;
    tmp = a.substr(index, e) ;
    index = e+2;
    int ret = getMethod(tmp) ;
    //如果是GET方法，解析路径名
    if(ret == GET) {
        getRequest(chl, tmp) ;
        return GET ;
    }
    //如果是post请求，找出content_length
    if(ret == POST) {
        postRequest(tmp, chl, a) ;
    }
    if(ret == DEFAULT) {
        return DEFAULT ;
    }
    return 0  ;  
}   

int process :: processArgGet(string tmp, channel* chl) {
    
    return 1 ;
}

//获取请求的长度
int process :: getContentLength(string a, channel* chl) {
    
    int l = chl->getReadBuffer()->getPostPos()  ;
    int pos = 0;
    if(l == -1) {
        pos= a.find("Content-Length:") ;
        //没找到，可能发的数据不够，也可能是请求头错误(少见)
        //设置的read buffer 长度为4096，第一个包里面80%有content-length
        if(pos == -1) {
            cout << __FILE__ << "     " << __LINE__ << endl ;
            return -1 ;
        }
        int flag = 0 ;
        string len ;
        for(int i=pos; i<(int)a.length(); i++) {
            if(flag == 1) {
                len+=a[i] ;
            }
            if(a[i] == '\r'||a[i] == '\n') {
                break ;
            }
            if(a[i] == ':')  {
                flag = 1 ;
            } 
        }
        l = atoi(len.c_str()) ;
        chl->getWriteBuffer()->setPostPos(l) ;
    }
    //确定提交的数据
    long p = a.find("\r\n\r\n") ;
    //根据\r\n\r\n找ontent-length获取信息
    string info ;
    int ret = getSubmitInfo(info, p+4, l, a, chl) ;
    //post只提交登录功能
    if(ret == 1) {
        //处理post请求
        int s = doPost(info) ;
        if(s == 1) {
            return -5;
        }
    }
    return l ;
}

int process :: doPost(string& info) {
    int index = info.find("name") ;
    string name ;
    for(int i=index+5; info[i] != '&'; i++) {
        name+=info[i] ;
    }

    string password ;
    index = info.find("password") ;
    for(int i=index+9; i< (int)info.size() ; i++) {
        password+=info[i] ;
    }
    //验证post请求
    if(name == "la" && password == "ha") {
        cout <<"验证成功！"<< endl ;
        return 0 ;
    }
    else {
         return 1 ;
    }
    return 1 ;
}
/*
//发送产生post请求的客户端套接字
int process :: sendSock(logBuf& buf, int fd, int connFd) {
    struct iovec iov ;
    struct msghdr msg ;
    int cmsghdrLen = CMSG_LEN(sizeof(int)) ;

    iov.iov_base = &buf ;
    iov.iov_len = sizeof(buf) ;
    msg.msg_iov = &iov ;
    msg.msg_iovlen = 1 ;
    msg.msg_name = NULL ;
    msg.msg_namelen = 0 ;

    std::shared_ptr<cmsghdr>msgptr = std::shared_ptr<cmsghdr>(new cmsghdr) ;
    msgptr->cmsg_level = SOL_SOCKET ;
    msgptr->cmsg_type = SCM_RIGHTS ;
    msgptr->cmsg_len = cmsghdrLen ;
    
    msg.msg_control = &(*msgptr) ;
    msg.msg_controllen = cmsghdrLen ;
    *(int*)CMSG_DATA(&(*msgptr)) = connFd ;
    if(sendmsg(fd, &msg, 0) < 0) {
        cout << __FILE__ << "      " << __LINE__ << endl ;
        return -1 ;
    }
    return 1 ;
}*/   
    
int process :: getSubmitInfo(string& info, int pos, int l, string &a, channel* chl) {
    long len = a.length() ;
    long i = pos ;
    //移动读指针
    while(i<len) {
        //往buf中添加信息
        info += a[i] ;
        i++ ;
        l-- ;
    }
    //用户态修改读取的字节数,每次来post请求读到l为０，表示post接收数据完成
    chl->getReadBuffer()->setPostPos(l) ;
    //如果post请求被读取完成
    //则需要验证信息后给浏览器资源返回资源
    if(l == 0) {
        return 1 ;
    }
    else {
        return -1 ;
    }    
}

void  process :: responseHead(channel* chl, string type, long len, int statusCode, string tip) {
     //发送响应头
    char buf[1024] ;
    //构造响应头
    string head ;
    sprintf(buf, "%s %d %s\r\nContent-Type: %s\r\nConnection: Keep-Alive\r\nContent-Length:%ld\r\n\r\n",
            version.c_str(), statusCode, tip.c_str(), type.c_str(),len) ;
    //将信息存入输入缓冲区中    
    int l = strlen(buf) ;
    //构造用户态缓冲区
    Buffer* input = chl->getWriteBuffer() ;
    for(int i=0; i<l; i++) {      
        input->append(buf[i]) ;
    }
}   

//处理get请求，发送响应头和
int process :: messageSend(const string& tmp, channel* chl) {
    //找出现第一个空格的地方
    if(flag == 0)
        getVersionPath(tmp) ;
    //构造响应头
    //解析路径名
    //如果路径只包含“/”，发送初始化页面
    if(paths == "/") {
        struct stat st ;
        int ret = stat("index.html", &st) ;
        if(ret < 0) {
            cout << __FILE__ << __LINE__ << endl ;
            return -1 ;
        }
        //获取文件的大小
        long len = st.st_size ;
        responseHead(chl, "text/html", len, 200, "OK") ;
        //将文件信息全部写入度缓冲区
        readFile("index.html", chl) ;
       // ret = sendFile(chl) ;
        //设置可写事件
        chl->enableWriting() ;
        //发送完数据关闭连接 
        ret = chl->updateChannel() ;
        if(ret < 0) {
            return -1 ;
        }
        return 1 ;
    }
    int ret = paths.find("php") ;
    //请求的文件是php文件
    if(ret != -1) {
        
    }   
    //将路径前面的/去掉
    if(flag == 0)
    paths = paths.c_str()+1 ;
    //获取资源类型,资源长度，状态码，提示语
    ret = isExist() ;
    chl->enableWriting() ;
    if(!ret) {
        cout << "发送404" << endl ;
        //发送404页面
        sendNotFind(chl) ;   
        chl->updateChannel() ;
    }
    //请求其他的资源
    else {
        cout << "资源存在！" << endl ;
        readFile(chl) ;
        chl->updateChannel() ;
    }
    flag  = 0 ;
    return 1 ;
}

void process :: readFile(channel* chl) {
    string type = getFileType() ; 
    struct stat st ;
    int ret  = stat(paths.c_str(), &st) ;
    if(ret < 0) {
        sendNotFind(chl) ;
        cout << __FILE__ << "    "<< __LINE__ << endl ;
        return ; 
    }
    long len = st.st_size;
    chl->setLen(len+1) ;
    responseHead(chl, type, len, 200, "OK") ;
    readFile(paths.c_str(), chl) ;
}

string process :: getFileType() {
    int index = paths.find(".") ;
    string type ;
    //没找到的话
    if(index == -1) {
        return "text/html" ;
    }
    else {
        int len = paths.length() ;
        type = paths.substr(index+1, len) ;
        if(type == "html"||type == "htm") {
            return "text/html" ;
        }
        if(type == "jpg") {
            return "image/jpg" ;
        }
        if(type == "png") {
            return "image/png" ;
        }
        if(type == "jpeg") {
            return "image/jpeg" ;
        }
        if(type == "pdf") {
            return "application/pdf" ;
        }
        if(type == "gif") {
            return "image/gif" ;
        }
        if(type == "au") {
            return "autio/au" ;
        }
        if(type == "mpeg") {
            return "video/mpeg" ;
        }
        if(type == "mp3") {
            return "audio/mpeg" ;
        }
        if(type == "wav"||type == "mp4") {
            return "audio/wav" ;
        }
        if(type == "ogg") {
            return "application/ogg" ;
        }
        if(type == "css") {
            return "text/css" ;
        }
    }
    return "text/plain;charset=utf-8" ;
}

//资源不可获取
void process :: sendNotFind(channel* chl) {
    struct stat st ;
    int ret = stat("404.html", &st) ;
    cout <<"错误类型："<< strerror(errno) << endl ;
    if(ret < 0) {
        cout << __FILE__ << "       " << __LINE__ << endl ;
        return  ;
    }
    int len = st.st_size ;
    responseHead(chl, "text/html", len, 404, "NOT FOUND") ;
    readFile("404.html", chl) ;
}

//读文件
void process :: readFile(const char* file, channel* chl) {
    int fd = open(file, O_RDONLY)  ;
    char p[100] ;
    getcwd(p, sizeof(p))  ;
    cout << file << "     " <<p<< endl ;
    if(fd < 0) {
        sendNotFind(chl) ;
        cout << __FILE__ << "    " << __LINE__  << endl ;
        return  ;
    }
    int len ;
    char buf[1024] ;
    Buffer* bf = chl->getWriteBuffer() ;
    //读文件
    int sum = 0 ;
    while(1) {
        len = readn(fd, buf, sizeof(buf)) ;
        if(len < 0) {
            cout << __FILE__ << "     " << __LINE__ << endl ;
            return ;
        }
        if(len == 0) {
            break ;
        }
        for(int i=0; i<len; i++) {
            bf->append(buf[i]) ;
        }
        sum+= len ;
        bzero(buf, sizeof(buf)) ;
    }
    
    chl->setLen(sum+1) ;
    close(fd) ;
}

//资源是否存在
int process :: isExist() {
    if(access(paths.c_str(), F_OK) != -1) {
        return 1 ;
    }
    else {
        return 0 ;
    }
}
//获取版本号和请求路径
int process :: getVersionPath(string tmp) {
    
    int pathIndex = tmp.find(' ') ;
    pathIndex += 1 ;
    while(tmp[pathIndex] != ' ') {
        paths += tmp[pathIndex] ;
        pathIndex++ ;
    }
    pathIndex++ ;
    while(pathIndex < (int)tmp.length()) {
        version += tmp[pathIndex] ;
        pathIndex ++ ;
    }
    return 1 ;   
}

//获取请求体
int process :: requestBody(channel* channel_) {
    
    return 1 ;
}

int process :: getMethod(string& line) {
    if((int)line.find("GET") != -1) {
        method = GET ;
        return GET ;
    }
    else if((int)line.find("POST") != -1) {
        method = POST ;
        return POST ;           
    }
    else {
        method = DEFAULT ;
        return DEFAULT ;
    }
}   
