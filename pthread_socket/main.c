#include "./include/socket.h"
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

void *xxx(void *arg) {

  int fd = *((int*)arg);
  printf("%d\n",fd);
  char buf[1024];
  while (1) {

    int ret = Read(fd, buf, 1024);
    if (ret == 0) {
      break;
    }

    write(STDOUT_FILENO, buf, ret);
    fgets(buf,1024,stdin);
    write(fd, buf, strlen(buf));
  }

  return (void *)0;
}

int main() {

  pthread_t tid;

  int s_fd = Socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sa;
  struct sockaddr_in c_sa;
  socklen_t len = sizeof(c_sa);
  sa.sin_family = AF_INET;
  sa.sin_port = htons(9999);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  Bind(s_fd, (struct sockaddr *)&sa, sizeof(sa));

  Listen(s_fd, 10);
  int c_fd;

  while (1) {
    c_fd = Accept(s_fd, (struct sockaddr *)&c_sa, &len);

   pthread_create(&tid,NULL,xxx,(void *)&c_fd);
    pthread_detach(tid);
  }

  return 0;
}