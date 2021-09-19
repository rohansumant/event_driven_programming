#include  <sys/types.h>
#include  <sys/event.h>
#include  <sys/time.h>

#include  <err.h>
#include  <fcntl.h>
#include  <signal.h>
#include  <stdio.h>
#include  <unistd.h>

#define MAX_LEN 1024

int main() {
  int kq = kqueue();
  struct kevent ev[1] = {0};
  struct timespec ts = { 2, 0 };
  char buff[MAX_LEN] = {0};
  EV_SET(ev, STDIN_FILENO, EVFILT_READ, EV_ADD, 0, 0, NULL);
  kevent(kq, ev, 1, NULL, 0, &ts);
  while(1) {
    int len;
    switch(kevent(kq, NULL, 0, ev, 1, &ts)) {
      case 0:
        printf("Hit timeout\n");
        break;

      case 1:
        len = read(STDIN_FILENO, buff, sizeof(buff)-1);
        buff[MAX_LEN-1] = 0;
        printf("%s\n",buff);
        break;
    }
  }
  return 0;
}
