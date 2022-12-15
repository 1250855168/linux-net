#include "include/socket.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  int c_fd = Socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(9999);
  inet_pton(AF_INET, "192.168.3.87", &sa.sin_addr);

  Connect(c_fd, (struct sockaddr *)&sa, sizeof(sa));

  char buf[1024];
  while (fgets(buf,1024, stdin) != NULL) {
    Write(c_fd, buf, (strlen(buf)));
    int ret = Read(c_fd, buf, 1024);
    if (ret == 0) {
      break;
    }

    write(STDOUT_FILENO, buf, ret);
  }
  Close(c_fd);

  return 0;
}