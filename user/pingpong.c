#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    char buf = 'p';
    int p[2];
    pipe(p);
    int pid = fork();
    if (pid == 0)
    {
        read(p[0], &buf, sizeof(char));
        printf("%d: received ping\n", getpid());
        write(p[1], &buf, sizeof(char));
        wait(0);
    }
    if (pid > 0)
    {
        write(p[1], &buf, sizeof(char));
        wait(0);
        read(p[0], &buf, sizeof(char));
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}