
#include <event2/event.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void read_cb(evutil_socket_t fd, short what, void *arg) {
  char buf[1024] = {0};

  int len = read(fd, buf, 1024);
  printf("string = %s,len =%d\n", buf, len);
  sleep(1);
}

int main() {

  unlink("xxx");
  mkfifo("xxx", 0644);

  int fd = open("xxx", O_RDONLY | O_NONBLOCK);
  if (fd == -1) {
    perror("open error");
  }

  struct event_base *base = event_base_new();

  struct event *ev = event_new(base, fd, EV_READ | EV_PERSIST, read_cb, NULL);

  event_add(ev, NULL);

  event_base_dispatch(base);

  event_free(ev);
  event_base_free(base);
  close(fd);

  return 0;
}