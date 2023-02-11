# 基于 Linux 的文件操作

对于 Linux 而言，一切皆是文件， socket 也被认为是文件的一种。用来操作文件 IO 的函数也可以拿来给 scoket 用。 Windows 与之不同的是， Windows 区分文件和 socket 。

socket 对于 Linux 而言即是文件描述符。文件描述符是操作系统分配给文件或者套接字的整数。实际上，我们常用的标准输入输出给被分配了文件描述符。

| 文件描述符 | 对象     |
|------------|----------|
| 0          | 标准输入 |
| 1          | 标准输出 |
| 2          | 标准错误 |

## 底层文件操作

### 打开文件

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * @param path 文件名的字符串地址
 * @param flag 文件打开模式信息
 * @return 成功时返回文件描述符，失败时返回 -1
 */
int open(const char *path, int flags);
```

文件打开模式：

| 打开模式      | 含义                       |
| ------------- | -------------              |
| O_CREAT       | 必要时创建文件             |
| O_TRUNC       | 删除全部现有数据           |
| O_APPEND      | 维持现有数据，保存到其后面 |
| O_RDONLY      | 只读打开                   |
| O_WRONLY      | 只写打开                   |
| O_RDWR        | 读写打开                   |

需要多个打开模式时，可以使用 `|` 进行连接，比如说 `O_CREAT | O_APPEND` 。

### 关闭文件

```c
#include <unistd.h>

/*
 * @param fd 需关闭文件的文件描述符
 * @return 成功时返回 0 ，失败时返回 -1
 */
int close(int fd);
```

### 写入文件

```c
#include <unistd.h>

/*
 * @param fd 需写入文件的文件描述符
 * @param buf 需保存数据的缓冲区地址
 * @param nbytes 传输字节数
 * @return 成功时返回写入的字节数，失败时返回 -1
 */
ssize_t write(int fd, const void * buf, size_t nbytes);
```

### 读取文件

```c
/*
 * @param fd 读取文件的文件描述符
 * @param buf 接受数据的缓冲区地址
 * @param nbytes 传输字节数
 * @return 成功时返回读入的字节数，失败时返回 -1
 */
#include <unistd.h>

ssize_t read(int fd, const void * buf, size_t nbytes);
```

### 文件描述符与套接字的比较

参看 `fd_seri.c` 。
