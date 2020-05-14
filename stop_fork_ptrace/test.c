#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf("hello from child\n");
    fork();
    return 0;
}