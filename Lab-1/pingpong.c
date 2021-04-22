#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int p_parent[2];
    int p_child[2];
    pipe(p_parent);
    pipe(p_child);
    int pid = fork();

    if (pid == 0)
    {
        char x[10];
        close(p_parent[1]);
        close(p_child[0]);
        read(p_parent[0], x, 1);
        printf("%d: received ping\n", getpid());
        close(p_parent[0]);
        write(p_child[1], x, 1);
        close(p_child[1]);
    }
    else 
    {
        char y[10];
        close(p_parent[0]);
        close(p_child[1]);
        write(p_parent[1],"x", 1);
        close(p_parent[1]);
        read(p_child[0], y, 1);
        printf("%d: received pong\n", getpid());
        close(p_child[0]);
    }
    exit(0);
}
