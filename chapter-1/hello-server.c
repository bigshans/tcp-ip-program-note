#include "../common.h"

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;

    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(-1);
    }

    // 创建套接字，返回套接字的文件描述符，是整数
    // PF_INET 协议族
    // AF_INET 地址族
    // 两者在实际情况中是相等的
    // SOCK_STREAM 建立面向连接的数据传输（TCP）
    // SOCK_DGRAM 建立起无连接的服务（UDP）
    // SOCK_RAW 原始套接字
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock < 0) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // htonl 和 htons 用于字节序转换
    // htonl 针对 32 位，4 字节 Host to Network Long
    // htons 针对 16 位，2 字节 Host to Network Short
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 绑定 sock 与地址
    if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        error_handling("bind() error");
    }

    // 将套接字转换为可连接的状态
    if (listen(serv_sock, 5) < 0) {
        error_handling("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    // 等待连接直到有连接为止
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if (clnt_sock < 0) {
        error_handling("accept() error");
    }

    // 写入数据到客户端，对于 Linux 来说，一切皆文件
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
