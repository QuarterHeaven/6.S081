#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  if (fork() == 0) {
    close(0);
    dup(p[0]);
    close(p[0]);
    char buf;
    if (read(0, &buf, 1)) {
      printf("%d: received ping\n", getpid());
      write(p[1], "x", 1);
    }
    close(p[1]);
  } else {
    write(p[1], "x", 1);
    close(p[1]);
    close(0);
    dup(p[0]);
    close(p[0]);
    char buf;
    if (read(0, &buf, 1)) {
      printf("%d: received pong\n", getpid());
    }
  }
  exit(0);
}
