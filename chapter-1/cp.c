#include "../common.h"

int main(int argc, char **argv)
{
    int source_fd, dest_fd;
    char buf[1024];
    if (argc < 3) {
        printf("Usage: %s source dest", argv[0]);
        return -1;
    }
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd < 0) {
        error_handling("Can't find source file");
    }
    // TODO: 文件模式存在问题
    dest_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRGRP | S_IWUSR | S_IRUSR);
    if (dest_fd < 0) {
        close(source_fd);
        error_handling("Can't create dest file");
    }
    ssize_t size;
    do {
        memset(buf, 0, sizeof(buf));
        size = read(source_fd, buf, sizeof(buf));
        if (size <= 0) {
            break;
        }
        lseek(source_fd, size, SEEK_CUR);
        size = write(dest_fd, buf, size);
        if (size <= 0) {
            break;
        }
        lseek(dest_fd, size, SEEK_CUR);
    } while(size > 0);
    close(source_fd);
    close(dest_fd);
    return 0;
}
