#include "../common.h"

int main()
{
    int fd;
    char buf[] = "Let's go!\n";
    // 创建空的只写文件
    fd = open("data.out", O_CREAT | O_WRONLY | O_TRUNC);
    if (fd < 0) {
        error_handling("open failed");
    }
    printf("file descriptor: %d\n", fd);
    if (write(fd, buf, sizeof(buf)) < 0) {
        error_handling("write failed");
        close(fd);
        exit(-1);
    }
    close(fd);
    return 0;
}
