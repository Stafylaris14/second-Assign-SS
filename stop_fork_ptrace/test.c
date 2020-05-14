#include <stdio.h>
#include <unistd.h>

int main (void)
{
    fork();
    printf("hello from child\n");
    fork();
    printf("hello from child1\n");
    return 0;
}