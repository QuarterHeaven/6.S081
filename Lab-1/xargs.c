#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  char j;
  char array[MAXARG];
  char *param[MAXARG];
  for (int i = 0; i < argc - 1; ++i) {
    param[i] = argv[i + 1];
  }
  char *p;
  p = array;
  int i = argc - 1;
  while (read(0, &j, sizeof(j))) {
    if (j == '\n' || j == ' ') {
      *p++ = 0;
      param[i] = array;
      ++i;
      if (j == '\n') {
        param[i] = 0;
        i = argc - 1;
        if (fork() == 0) {
          p = array;
          wait(0);
        } else {
          exec(param[0], param);
        }
      }
      continue;
    }
    *p = j;
    p++;
  }

  exit(0);
}