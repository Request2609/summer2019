#include <iostream>
#include<vector>
#include<unistd.h>
#include<fcntl.h>
#include<sys/uio.h>
using namespace std ;

int main()
{
    vector<char>s ;
    char buf[100]={0} ;
    struct iovec iov[2] ;
    
    iov[0].iov_base = &(*s.begin()) ;
    iov[0].iov_len = s.capacity() ;
    iov[1].iov_base = buf ;
    iov[1].iov_len = sizeof(buf) -1;

    int fd = open("test.txt", O_RDWR) ;
    if(fd < 0) {
        cout << "test" << endl ;
        return 0;
    }
    cout << s.capacity()<< endl  ;
    readv(fd, iov, 2) ;
    for(char c : s) {
        cout << c <<"" ;
    }
    cout << endl ;
    cout << buf << endl ;
    close(fd) ;
    return 0;
}

