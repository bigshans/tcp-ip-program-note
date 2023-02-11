#include "../common.h"
#define BUF_SIZE 100

int main(int argc, char *argv[])
{
    int fd;
    char buf[BUF_SIZE];

    fd = open("./data.out", O_RDONLY);
    if (fd < 0) {
        error_handling("open failed");
    }
    printf("file descriptor: %d\n", fd);

    if (read(fd, buf, sizeof(buf)) < 0) {
        error_handling("read error");
        close(fd);
        exit(-1);
    }
    printf("file data: %s", buf);
    close(fd);
    return 0;
}
