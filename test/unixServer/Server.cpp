#include "Server.h"

void server :: process() {
    if(logIn()) {
        //暂时提供一种服务
        switch(buf->type) {
            case 1 :
                std:: cout << "发送文件！" << std:: endl ;
                sendHtml() ;
                break ;
        }
    }
    else {
        //重新构造头部
        sendNotFind() ;      
    }
}

int server :: sendHtml() {
    std::string paths = buf->path_ ;
    struct stat st ;
    int ret = stat(paths.c_str(), &st) ;
    if(ret < 0) {
        sendNotFind() ;   
        return -1 ;
    }
    else {
        paths = paths.c_str()+1 ;
        std::string type = getFileType(paths) ;
        responseHead(type, st.st_size, OK, "OK") ;
        readFile(paths.c_str()) ;
        sendToBrower() ;
    }
    return 1 ;
}

std::string server :: getFileType(std::string file) {
    int index = file.find(".") ;
    std::string type ;
    //没找到的话
    if(index == -1) {
        return "text/html" ;
    }   
    else {
        int len = file.length() ;
        type = file.substr(index+1, len) ;
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
void server :: sendNotFind() {
    struct stat st ;
    int ret = stat("404.html", &st) ;
    if(ret < 0) {
        std::cout << __FILE__ << "       " << __LINE__ << std::endl ;
        return  ;
    }
    int len = st.st_size ;
    responseHead("text/html", len, 404, "NOT FOUND") ;
    readFile("404.html") ;
    sendToBrower() ;
}

//发送给浏览器
int  server :: sendToBrower() {
    //写缓冲区
    int connFd = chl->getConnFd() ;
    std:: cout << connFd << std::endl ;
    char buff[SIZE] ;
    int j = 0 ; 
    bzero(buff, sizeof(buff)) ;
    int start = buffer_.getReadIndex() ;
    int len = buffer_.getWriteIndex()-start ;
    //文件长度小于4096
    int sum = 0 ; 
    if(len < SIZE) {
        for(int i=start; i< len; i++) {
            buff[j] = buffer_[i] ;
            j++ ;
        }

        buff[j] = '\0' ;
        std::cout << buf << std::endl ;
        //写文件长度
        int ret = writen(connFd, buf, sizeof(buf)) ;
        if(ret < 0) {
            std :: cout <<strerror(errno)<<"    " << __FILE__ << "     "<<__LINE__ << std:: endl ;
            return -1 ;
        }   
        sum+= ret ;
        close(connFd) ;
        buffer_.clear() ;
        //返回１表示可以将连接关闭掉,同事将本channel从EventLoop中删除
        return  1;  
    }   

    int ret = 0 ; 
    //文件长度大于4096
    for(int i=start; i<len; i++) {
        if(j == SIZE) {
            buff[j] = '\0' ;
            ret = writen(connFd, buf, sizeof(buf)) ;
            if(ret < 0) {
                std::cout << __FILE__ << "     "  << __LINE__<<"      " <<strerror(errno) <<"       num:"<< errno<< std::endl ;   
                return -1 ;
            }   
            sum += ret ;
            bzero(buff, sizeof(buff)) ;
            j = 0 ; 
        }   
        buff[j] = buffer_[i] ;
        buffer_.moveRead() ;
        j++ ;
    }   

    if(strlen(buff) > 0) {
        ret = writen(connFd, buf, sizeof(buf)) ;
        if(ret < 0) {
            std :: cout << __FILE__ << "      " << __LINE__ << std::endl ;
            return -1 ;
        }   
        sum+= ret ;
    }   
    std::cout << "发送字节数--------------------------------------=======----->" << sum << std::endl ;
    buffer_.clear() ;
    int fd = chl->getFd() ;
    //关闭Unix域套接字
    close(connFd) ;
    close(fd) ;
    return 1 ; 
}

//登录界面
int server :: logIn() {
    if(strcmp(buf->name, "ck")&&strcmp(buf->password, "ck")) {
        std::cout << "登录成工！" << std::endl ;
        return 0 ;
    }
    return 1 ;
}

//读文件
void server :: readFile(const char* file) {
    int fd = open(file, O_RDONLY)  ;
    if(fd < 0) {
        sendNotFind() ;
        std::cout << __FILE__ << "    " << __LINE__  << std::endl ;
        return  ;
    }
    int len ;
    char buf[1024] ;
    //读文件
    int sum = 0 ;
    while(1) {
        len = readn(fd, buf, sizeof(buf)) ;
        if(len < 0) {
            std::cout << __FILE__ << "     " << __LINE__ <<std::endl ;
            return ;
        }
        if(len == 0) {
            break ;
        }
        for(int i=0; i<len; i++) {
            buffer_.append(buf[i]) ;
        }
        sum+= len ;
        bzero(buf, sizeof(buf)) ;
    }
    std::cout << "读到的字节大小：--------------------------------------------------------------------->" << sum << std::endl ;
    close(fd) ;
}

//传入缓冲区
void  server :: responseHead(std::string type, long len, int statusCode, std::string tip) {
    //发送响应头
    char bufer[1024] ;
    //构造响应头
    std::string head ;
    sprintf(bufer, "%s %d %s\r\nContent-Type: %s\r\nConnection: Keep-Alive\r\nContent-Length:%ld\r\n\r\n",
            buf->version, statusCode, tip.c_str(), type.c_str(),len) ;
    //将信息存入输入缓冲区中
    int l = strlen(bufer) ;

    //构造用户态缓冲区
    for(int i=0; i<l; i++) {
        buffer_.append(bufer[i]) ;
    }
}
