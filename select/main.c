#include "include/socket.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#define SERV_PORT 6666

int main() {

  int s_fd, c_fd;

  s_fd = Socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in s_sa, c_sa;
  s_sa.sin_port = htons(SERV_PORT);
  s_sa.sin_family = AF_INET;
  s_sa.sin_addr.s_addr = htonl(INADDR_ANY);
  socklen_t salen = sizeof(s_sa);

  Bind(s_fd, (struct sockaddr *)&s_sa, salen);

  Listen(s_fd, 99);

  fd_set set, allset;
  int maxfd = s_fd;

  FD_ZERO(&allset);
  FD_SET(s_fd, &allset);

  while (1) {

    set = allset;
    int ret = select(maxfd + 1, &set, NULL, NULL, NULL);

    if (FD_ISSET(s_fd, &set)) {
      c_fd = Accept(s_fd, (struct sockaddr *)&c_sa, &salen);
      FD_SET(c_fd, &allset);

      if (c_fd > maxfd) {
        maxfd = c_fd;
      }
      if (ret == 1) {
        continue;
      }
    }
    for (int i = s_fd + 1; i < maxfd + 1; i++) {
      if (FD_ISSET(i, &set)) {

        char buf[BUFSIZ];

        int ret = Read(i, buf, 1024);
        if (ret==0)
        {
           Close(i);
           FD_CLR(i,&allset);
           break;
        }

        Write(STDOUT_FILENO,buf,ret);
      }
    }
  }

  close(s_fd);

  return 0;
}