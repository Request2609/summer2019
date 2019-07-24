#pragma once
#include<vector>
#include<string>
#include<assert.h>
#include<string.h>
class Buffer
{
    //用户缓冲区应该和套接字进行绑定
public:
    Buffer(std::string buf) ;
    Buffer(const char* buf) ;
    Buffer() ;
    ~Buffer() {}
public :
    std :: string readBuffer(int start, int end) ;
    int retreiveBuffer(int start, int end) ;
    int retreiveBuffer(int n) ;
    void bufferClear() ;
private:
    //开始读的地方
    int readIndex = 0;
    //开始写的地方
    int writeIndex = 0;
    std::vector<char> buffer ;
};


