#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // unix std
#include <arpa/inet.h> // 定义了 internet 相关的操作
#include <sys/socket.h> // 套接字库
#define cls(p) memset(&p, 0, sizeof(p))

void error_handling(char* message)
{
    fputs(message, stderr);
    putc('\n', stderr);
    exit(1);
}

#endif
