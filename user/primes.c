#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int pp)
{
    int num;
    if (read(pp, (char *)(&num), 1) != 0)
    {
        printf("prime %d\n", num);
        int p[2];
        pipe(p);
        if (fork() == 0)
        {
            close(p[1]);
            prime(p[0]);
        }
        else
        {
            int temp;
            while (read(pp, (char *)(&temp), 1) != 0)
                if (temp % num != 0)
                    write(p[1], (char *)&temp, 1);
            close(p[1]);
            close(p[0]);
            close(pp);
            wait(0);
        }
    }
    else
        close(pp);
}
int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        prime(p[0]);
    }
    else
    {
        for (int i = 2; i < 36; i++)
        {
            write(p[1], (char *)(&i), 1);
        }
        close(p[1]);
        close(p[0]);
        wait(0);
    }
    exit(0);
}