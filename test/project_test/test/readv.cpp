#include <iostream>
#include<unistd.h>
#include<fstream>
#include<sys/uio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
/*
struct iovec {
    void* iov_base ;//开始地址
    size_t iov_len ; //有效字符的个数
} ;
*/
#include<string.h>
const char *str1 = "hello world" ;
const char *str2 = "Linux is greatest OS" ;
using namespace std ;
int main()
{   
    int ret, len ;
    
    struct iovec iov[2] ;
    iov[0].iov_base = (void*)str1 ;
    iov[0].iov_len = strlen(str1) ;

    iov[1].iov_base = (void*)str2 ;
    iov[1].iov_len = strlen(str2) ;
    len = iov[1].iov_len + iov[0].iov_len ;
    int fd = open("test.txt", O_CREAT|O_RDWR, 0666) ;
    if(fd < 0) {
        return 1;
    }
    //往文件中写东西
    ret = writev(fd, iov, 2) ;
    if(ret != len) {
        cout << "error!" << endl ;
        return 1 ;
    }
    close(fd) ;

    int fd1 ;
    //读文件中的信息
    if((fd1 = open("test.txt", O_RDWR)) < 0) {
        cout << "打开文件失败！" << endl ;
        return  0 ;
    }
    char readBuf1[20] = {0} ;
    char readBuf2[10]  = {0};
    struct iovec iov1[2] ;
    iov1[0].iov_base = readBuf1 ;
    iov1[1].iov_base = readBuf2 ;
    //iov_len的值为所设置有效字符的长度，不能包括\0
    iov1[0].iov_len = sizeof(readBuf1)-1  ;
    iov1[1].iov_len = sizeof(readBuf2)-1 ;
    int nread = readv(fd1, iov1, 2) ;
    cout << "读到数据：" << nread << "字节" << endl ;
    cout << readBuf1 << endl ;
    cout << readBuf2 << endl ;
    close(fd1) ;
    exit(EXIT_SUCCESS) ;
    return 0;
}

