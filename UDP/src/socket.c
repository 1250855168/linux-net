#include "../include/socket.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void perr_exit(const char *s) {
  perror(s);
  exit(-1);
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr) {
  int ret;
again:
  ret = accept(fd, sa, salenptr);
  if (ret == -1) {
    if (errno == ECONNABORTED||errno == EINTR) // 软件引起的 连接 中止 ECONNABORTED    EINTR 中断影响 
    {
      goto again;
    }
    else{
        perr_exit("accept error");
    }
  }
  return ret;
}

int Bind(int fd, const struct sockaddr *sa, socklen_t salen){
        int n;

	if ((n = bind(fd, sa, salen)) < 0)
		perr_exit("bind error");

    return n;
}

int Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    int n;

	if ((n = connect(fd, sa, salen)) < 0)
		perr_exit("connect error");

    return n;
}

int Listen(int fd, int backlog)
{
    int n;

	if ((n = listen(fd, backlog)) < 0)
		perr_exit("listen error");

    return n;
}

int Socket(int family, int type, int protocol)
{
	int n;

	if ((n = socket(family, type, protocol)) < 0)
		perr_exit("socket error");

	return n;
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;

again:
	if ( (n = read(fd, ptr, nbytes)) == -1) {
		if (errno == EINTR)
			goto again;
		else
			return -1;
	}
	return n;
}


ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
	ssize_t n;

again:
	if ( (n = write(fd, ptr, nbytes)) == -1) {
		if (errno == EINTR)
			goto again;
		else
			return -1;
	}
	return n;
}

int Close(int fd)
{
    int n;
	if ((n = close(fd)) == -1)
		perr_exit("close error");

    return n;
}