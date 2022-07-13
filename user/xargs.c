#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char* argv[]) {
  char buf[MAXARG], *p;
  char *args[MAXARG];
  int count = 0;
  char tmp[MAXARG][100];

  for (int i = 1; i < argc; ++ i) {
    args[i - 1] = argv[i];
//    printf("%s, %s\n", args[i - 1], argv[i]);
  }

  p = buf;
  while (read(0, p, sizeof(char))) {
    if (*p != '\n') {
      p++;
      continue;
    }

    *p = 0;
    p = buf;
    strcpy(tmp[count], buf);
    args[argc + count - 1] = tmp[count];
    count ++;
    if (*p == ' ') continue;
    args[argc + count] = 0;
    count = 0;

    if (fork() == 0) {
      /* printf("argv = %s\nargv={", argv[1]); */
      /* for (int j = 0; j < MAXARG; j++) { */
      /*   if (args[j] == 0) break; */
      /*   printf("%s, ", args[j]); */
      /* } */
      /* printf("}\n"); */
      exec(argv[1], args);
      exit(0);
    } else {
      count = argc;
      wait((int *) 0);
    }
  }
  exit(0);
}
