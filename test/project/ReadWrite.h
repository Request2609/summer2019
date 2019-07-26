#pragma once
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>

int readn(int fd, void*buf, int n) ;
int writen(int fd, void* buf, int n) ;
