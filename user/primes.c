#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int p[2])
{
    char nums[35];
    int val = 0;
    read(p[0], nums, 35);
    for (int i = 2; i < 35; i++)
    {
        if (nums[i] == 1)
        {
            val = i;
            nums[i] = 0;
            break;
        }
    }
    if (val == 0)
        exit(0);
    printf("prime %d\n", val);
    for (int i = 2; i < 35; i++)
    {
        if (i % val == 0)
            nums[i] = 0;
    }
    int pid = fork();
    if (pid > 0)
    {
        write(p[1], nums, 35);
        wait(0);
    }
    else if (pid == 0)
    {
        prime(p);
    }
}
int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    char nums[35];
    for (int i = 2; i < 35; i++)
    {
        nums[i] = 1;
    }
    printf("%s", nums);
    int pid = fork();
    if (pid == 0)
    {
        prime(p);
        wait(0);
    }
    else if (pid > 0)
    {
        write(p[1], nums, 35);
        wait(0);
    }
    exit(0);
}