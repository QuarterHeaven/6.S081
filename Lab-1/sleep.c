#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int i;
    char *b[]={"Error: No argument imputed\n"};
    if (argc == 1) {
        write(1, b[0], strlen(b[0]));
        exit(-1);
    }

    i = atoi(argv[1]);
    sleep(i);
    exit(0);
}
