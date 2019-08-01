#pragma once
#include<iostream>
#include<vector>

class buffer
{
public:
    buffer() :readIndex(0), writeIndex(0){}
    ~buffer() {}
public :
    int size() { return info.size() ; }
    void append(char i) { writeIndex++; info.push_back(i) ; }
    int getReadIndex() { return readIndex ; }
    int getWriteIndex() {return writeIndex ;}
    char operator[](int i) ;
private:
    int readIndex ;
    int writeIndex ;
    std::vector<char> info ;
};

