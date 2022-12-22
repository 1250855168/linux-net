#include "./include/socket.h"
#include <arpa/inet.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>   //struct sockaddr_un
#include <unistd.h>

int main() {

  int s_fd = Socket(AF_UNIX, SOCK_STREAM, 0);

  struct sockaddr_un s_sa, c_sa;
  s_sa.sun_family = AF_UNIX;
  strcpy(s_sa.sun_path, "SERV_ADDR");

  unlink("SERV_ADDR");
  Bind(s_fd, (struct sockaddr *)&s_sa, sizeof(s_sa.sun_path));

  Listen(s_fd, 20);

  while (1) {
    socklen_t len = offsetof(struct sockaddr_un, sun_path) + sizeof("SERV_ADDR");
    int c_fd = Accept(s_fd, (struct sockaddr *)&c_sa, &len);

    while (1) {
      char buf[1024];
      int ret = Read(c_fd, buf, 1024);
      if (ret == 0) {
        break;
      }
      Write(STDIN_FILENO, buf, ret);
      Write(c_fd, buf, ret);
    }

    Close(c_fd);
  }

  close(s_fd);

  return 0;
}