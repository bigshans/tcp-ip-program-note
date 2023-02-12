#include "../common.h"

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in addr;
    char message[30];;
    int str_len = 0;
    int idx = 0, read_len = 0;
    if (argc != 3) {
        printf("Usage : %s <IP> <port>", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        error_handling("socket() error");
    }
    cls(addr);
    addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr))) {
        error_handling("connect() error");
    }

    while (read_len = read(sock, &message[idx++], 1)) {
        if (read_len == -1) {
            error_handling("read() error");
        }
        str_len += read_len;
    }

    printf("Message from server: %s\n", message);
    printf("Function read call count: %d\n", str_len);
    close(sock);
    return 0;
}
