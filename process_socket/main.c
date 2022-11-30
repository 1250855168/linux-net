#include "./include/socket.h"
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

void sig_chi(int sig) {
  int status;
  while (waitpid(0, &status, WNOHANG) > 0) {
    printf("wait pid = %d", status);
  }
}

int main() {

  struct sigaction act;
  act.sa_flags = 0;
  act.sa_handler = sig_chi;
  sigemptyset(&act.sa_mask);
  sigaction(SIGCHLD, &act, NULL);

  int s_fd = Socket(AF_INET, SOCK_STREAM, 0);
  printf("%d\n",s_fd);

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
    c_fd= Accept(s_fd, (struct sockaddr *)&c_sa, &len);
    pid_t pid = fork();

    if (pid == 0) {
      Close(s_fd);
      while (1) {
        char buf[1024];
        int ret = Read(c_fd, buf, 1024);
        if (ret == 0) {
          break;
        } else {
          Write(STDOUT_FILENO, buf, ret);
        }
      }
      Close(c_fd);
      return 0;

    } else if (pid > 0) {
      Close(c_fd);
      continue;
    } else {
      perr_exit("fork error");
    }
  }

  return 0;
}