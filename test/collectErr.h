#ifndef _COLLECTION_H_
#define _COLLECTION_H_
#include<iostream>
#include<fstream>
#include<time.h>
#include<stdint.h>
#include<sys/time.h>
//记录所有错误
void writeErr(const char* fileName, int line) {
    std::ofstream ofs("log", std::ios::out|std::ios::app) ;
    if(ofs.fail()) {
        std :: cout << "记录日志文件出错！" << std :: endl ;
        exit(1) ;
    }
    struct timeval tv ;
    gettimeofday(&tv, NULL) ;
    int64_t sec = tv.tv_sec ;
    struct tm curTm ;
    localtime_r((time_t*)&sec, &curTm) ;
    char curTime[20] ;
    snprintf(curTime, 20,"%d-%02d-%02d %02d:%02d:%02d", curTm.tm_year+1900, curTm.tm_mon+1, curTm.tm_mday, curTm.tm_hour, curTm.tm_min,  curTm.tm_sec) ;
    ofs << fileName << line << "  " << curTime << std::endl ;
    ofs.close() ;
}

#endif
