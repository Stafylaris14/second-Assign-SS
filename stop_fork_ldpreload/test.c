#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf("eimai prin to fork\n");

    pid_t a = fork();
    printf("eimai meta to fork\n");
    return 0;
}