
#include "./include/socket.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  int fd = Socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in sa, c_sa;

  sa.sin_family = AF_INET;
  sa.sin_port = htons(9999);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  Bind(fd, (struct sockaddr *)&sa, sizeof(sa));

  while (1) {

    char buf[1024];
    socklen_t len = sizeof(sa);
    int ret = recvfrom(fd, buf, 1024, 0, (struct sockaddr *)&c_sa, &len);
    if (ret == 0) {
      break;
    }
    Write(STDOUT_FILENO, buf, ret);
    sendto(fd, buf, ret, 0, (struct sockaddr *)&c_sa, len);
  }
  Close(fd);
  return 0;
}