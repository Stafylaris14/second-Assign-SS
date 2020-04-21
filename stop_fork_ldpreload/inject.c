#include <unistd.h>
#include <stdio.h>

pid_t fork(void)
{
    fprintf(stderr , "I am sory but you cant invoke fork :(\n");
    return -1;
}
