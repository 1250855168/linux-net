#include "include/socket.h"
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  int s_fd = Socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in s_sa, c_sa;
  s_sa.sin_family = AF_INET;
  s_sa.sin_port = htons(9999);
  s_sa.sin_addr.s_addr = htonl(INADDR_ANY);
  Bind(s_fd, (struct sockaddr *)&s_sa, sizeof(s_sa));

  int opt = 1;
  setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  Listen(s_fd, 128);

  int e_head = epoll_create(1);

  struct epoll_event event, events[1024];
  event.events = EPOLLIN;
  event.data.fd = s_fd;
  epoll_ctl(e_head, EPOLL_CTL_ADD, s_fd, &event);

  while (1) {

    int is_events = epoll_wait(e_head, events, 1024, -1);
    for (int i = 0; i < is_events; i++) {
      if (events[i].data.fd == s_fd) {
        socklen_t len = sizeof(c_sa);
        int c_fd = Accept(s_fd, (struct sockaddr *)&c_sa, &len);
        event.events = EPOLLIN;
        event.data.fd = c_fd;
        epoll_ctl(e_head, EPOLL_CTL_ADD, c_fd, &event);
      } else {

        char buf[BUFSIZ];

        int ret = Read(events[i].data.fd, buf, BUFSIZ);
        if (ret == 0) {
          epoll_ctl(e_head, EPOLL_CTL_DEL, events[i].data.fd, &event);
          close(events[i].data.fd);
        }
        if (ret == -1) {
          epoll_ctl(e_head, EPOLL_CTL_DEL, events[i].data.fd, &event);
          close(events[i].data.fd);
        }

        Write(STDIN_FILENO, buf, ret);
        Write(events[i].data.fd, buf, ret);
      }
    }
  }

  Close(s_fd);

  return 0;
}