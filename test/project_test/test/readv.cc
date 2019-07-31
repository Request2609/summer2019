#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>
#include <fcntl.h>
int main()
{
    char buf1[2] = { 0 };
    char buf2[20] = { 0 };
    struct iovec iov[2];
    ssize_t nread;

    iov[0].iov_base = buf1;
    iov[0].iov_len = sizeof(buf1) - 1;
    iov[1].iov_base = buf2;
    iov[1].iov_len = sizeof(buf2) - 1;
    int fd = open("test.txt", O_RDWR) ;
    nread = readv(fd, iov, 2);
    printf("%ld bytes read.\n", nread);
    printf("buf1: %s\n", buf1);
    printf("buf2: %s\n", buf2);

    exit(EXIT_SUCCESS);
}


