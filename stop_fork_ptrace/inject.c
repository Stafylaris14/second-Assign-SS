#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

int main(void)
{
    pid_t pid;
    int count = 0;
    int wait_status;
    int enter_syscall = 1;

    pid = fork();
    if (pid == 0)
    {
        ptrace(PTRACE_TRACEME, NULL, NULL, NULL);
        execl("/bin/date", "date", NULL);
    }
    else if (pid > 0)
    {
        wait(&wait_status);
        while (1)
        {
            if(enter_syscall)
            {
                count++;
                enter_syscall = 0;
            }else
            {
                enter_syscall = 1;
            }
            

            ptrace(PTRACE_SYSCALL , pid , NULL , NULL);
            wait(&wait_status);
            if(WIFEXITED(wait_status)) break;
        }
    }
    else{
        printf("error\n");
        
    }
    printf("einai %d toso polla\n" , count);
}