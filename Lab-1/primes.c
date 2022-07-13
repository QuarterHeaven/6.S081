#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void p_prime() {
  int prime;
  if (read(0, &prime, sizeof(int))) {
    printf("prime %d\n", prime);
  } else {
    return;
  }
  int p[2];
  int t;
  pipe(p);
  if (fork()) {
    close(p[1]);
    close(0);
    dup(p[0]);
    close(p[0]);
    p_prime();
  } else {
    close(p[0]);
    close(1);
    dup(p[1]);
    close(p[1]);
    while(read(0, &t, sizeof(int))) {
      if (t % prime) {
        write(1, &t, sizeof(int));
      }
    }
  }
}

int
main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  int i;
  if (fork()) {
    close(p[1]);
    close(0);
    dup(p[0]);
    close(p[0]);
    p_prime();
  } else {
    close(p[0]);
    close(1);
    dup(p[1]);
    close(p[1]);
    for (i = 2; i <= 35; ++i) {
      write(1, &i, sizeof(int));
    }
    wait((int*) 0);
  }
  exit(0);
}
