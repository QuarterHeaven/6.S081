#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime()
{
    int p[2];
    int i, j;
    if (read(0, &i, sizeof(i)))
    {
        printf("prime %d\n", i);
    }
    else
    {
        exit(0);
    }

    pipe(p);

    if (fork() == 0)
    {
        close(1);
        dup(p[1]);
        close(p[0]);
        close(p[1]);
        while(read(0, &j, sizeof(j)))
        {
            if (j % i != 0)
            {
                write(1, &j, sizeof(j));
            }
        }
    }
    else
    {
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        prime();
    }
}

int main()
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        close(1);
        dup(p[1]);
        close(p[0]);
        close(p[1]);
        for (int i = 2; i <= 35; ++i)
        {
            write(1, &i, sizeof(i));
        }
        wait(0);
    }
    else
    {
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        prime();
    }
    exit(0);
}
