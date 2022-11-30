#include "./include/socket.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>
#include<string.h>

int main() {

  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(9999);
  inet_pton(AF_INET, "192.168.126.1", &sa.sin_addr.s_addr);

  int fd = Socket(AF_INET, SOCK_STREAM, 0);

  Connect(fd, (struct sockaddr *)&sa, sizeof(sa));

  char buf[1024];
  while (fgets(buf,1024, stdin) != NULL) {
    Write(fd, buf, (strlen(buf)));
    int ret = Read(fd, buf, 1024);
    if (ret == 0) {
      break;
    }

    write(STDOUT_FILENO, buf, ret);
  }

  return 0;
}