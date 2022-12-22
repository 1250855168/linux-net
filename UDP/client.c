
#include "./include/socket.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  int fd = Socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in sa;

  sa.sin_family = AF_INET;
  sa.sin_port = htons(9999);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  while (1) {

    char buf[1024];
    fgets(buf, 1024, stdin);

    sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&sa, 1024);

    socklen_t len = sizeof(sa);
    int ret = recvfrom(fd, buf, 1024, 0, NULL, 0);
    Write(STDOUT_FILENO, buf, ret);
  }

  Close(fd);

  return 0;
}