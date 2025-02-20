#include <stdfil.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>

int main(int argc, char** argv)
{
    int fd = zsys_open("filc/tests/fileio/test.txt", 0);
    ZASSERT(fd > 2);

    char buf[100];
    __builtin_memset(buf, 0, sizeof(buf));
    int result = zsys_read(fd, buf, sizeof(buf));
    ZASSERT(result == 14);
    zprintf("read the zsys way: %s", buf);
    ZASSERT(!zsys_close(fd));

    fd = open("filc/tests/fileio/test.txt", O_RDONLY);
    ZASSERT(fd > 2);
    __builtin_memset(buf, 0, sizeof(buf));
    result = read(fd, buf, sizeof(buf));
    ZASSERT(result == 14);
    zprintf("read with read way: %s", buf);
    ZASSERT(!close(fd));

    FILE* fin = fopen("filc/tests/fileio/test.txt", "r");
    ZASSERT(fin);
    __builtin_memset(buf, 0, sizeof(buf));
    result = fread(buf, 1, sizeof(buf), fin);
    ZASSERT(result == 14);
    printf("read the fread way: %s", buf);
    fclose(fin);

    fd = open("filc/tests/fileio/test.txt", O_RDONLY);
    int fd2 = fcntl(fd, F_DUPFD, 100);
    ZASSERT(fd2 >= 100);
    __builtin_memset(buf, 0, sizeof(buf));
    result = read(fd2, buf, sizeof(buf));
    ZASSERT(result == 14);
    zprintf("read with fcntl DUPFD read way: %s", buf);
    __builtin_memset(buf, 0, sizeof(buf));
    result = read(fd, buf, sizeof(buf));
    ZASSERT(!result);
    ZASSERT(!close(fd));

    struct flock flock;
    memset(&flock, 0, sizeof(flock));
    flock.l_type = F_RDLCK;
    int res = fcntl(fd2, F_GETLK, &flock);
    ZASSERT(!res);
    ZASSERT(flock.l_type == F_UNLCK);
    ZASSERT(!flock.l_whence);
    ZASSERT(!flock.l_start);
    ZASSERT(!flock.l_len);
    ZASSERT(!flock.l_pid);
    ZASSERT(!close(fd2));
    
    fd = open("filc/tests/fileio/test.txt", O_RDONLY);
    flock.l_type = F_WRLCK;
    res = fcntl(fd, F_GETLK, &flock);
    ZASSERT(!res);
    ZASSERT(flock.l_type == F_UNLCK);
    ZASSERT(!flock.l_whence);
    ZASSERT(!flock.l_start);
    ZASSERT(!flock.l_len);
    ZASSERT(!flock.l_pid);

    res = fcntl(fd, F_GETFD);
    ZASSERT(!res);

    res = fcntl(fd, F_SETFD, FD_CLOEXEC);
    ZASSERT(!res);

    res = fcntl(fd, F_GETFD);
    ZASSERT(res == FD_CLOEXEC);

    ZASSERT(!isatty(fd));
    ZASSERT(!close(fd));

    int fds[2];
    ZASSERT(!pipe(fds));
    ZASSERT(write(fds[1], "hello", strlen("hello") + 1) == strlen("hello") + 1);

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fds[0], &readfds);
    ZASSERT(select(fds[0] + 1, &readfds, NULL, NULL, NULL) == 1);
    ZASSERT(FD_ISSET(fds[0], &readfds));
    ZASSERT(pselect(fds[0] + 1, &readfds, NULL, NULL, NULL, NULL) == 1);
    ZASSERT(FD_ISSET(fds[0], &readfds));
    
    ZASSERT(read(fds[0], buf, strlen("hello") + 1) == strlen("hello") + 1);
    ZASSERT(!strcmp(buf, "hello"));

    int dupfd = dup(fds[0]);
    ZASSERT(dupfd > 2);
    ZASSERT(write(fds[1], "world", strlen("world") + 1) == strlen("world") + 1);
    ZASSERT(read(dupfd, buf, strlen("world") + 1) == strlen("world") + 1);
    ZASSERT(!strcmp(buf, "world"));
    
    dupfd = dup2(fds[0], 100);
    ZASSERT(dupfd == 100);
    ZASSERT(write(fds[1], "witam", strlen("witam") + 1) == strlen("witam") + 1);
    ZASSERT(read(dupfd, buf, strlen("witam") + 1) == strlen("witam") + 1);
    ZASSERT(!strcmp(buf, "witam"));
    
    return 0;
}


