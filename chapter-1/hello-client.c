#include "../common.h"

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if (argc != 3) {
        printf("Usage : %s <IP> <port>", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error_handling("socket() error");
    }

    cls(serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // 绑定之后发送连接请求
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
        error_handling("connect() error");
    }

    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len < 0) {
        error_handling("read() error");
    }

    printf("Message from server: %s\n", message);
    close(sock);
    return 0;
}
