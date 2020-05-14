#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>

#include <syscall.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int is_blocked(long arg);


int main()
{
  pid_t child;

  child = fork();
  if (child == 0)
  {

    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execl("test", "test", NULL);
  }
  else
  {
    int status;

    int isBlocked = 0;
    while (!WIFEXITED(status))
    {
      ptrace(PTRACE_SYSCALL, child, 0, 0);
      wait(&status);
      struct user_regs_struct regs;
      isBlocked = 0;
      ptrace(PTRACE_GETREGS, child, NULL, &regs);

      if (is_blocked(regs.orig_rax))
      {
        isBlocked = 1;
        regs.orig_rax = -1;
        ptrace(PTRACE_SETREGS, child, 0, &regs);
      }

      ptrace(PTRACE_SYSCALL, child, NULL, NULL);
      wait(&status);

      if (isBlocked)
      {
        regs.rax = -EPERM; 
        ptrace(PTRACE_SETREGS, child, 0, &regs);
      }
    }
  }
  exit(0);
}

int is_blocked(long arg)
{

  if (arg == SYS_clone) //56 -> SYS_clone
  {
    // printf("fork DETECTED\n");
    return 1;
  }
  return 0;
}
