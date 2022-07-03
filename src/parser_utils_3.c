#include "main.h"

void	dfl(int sig)
{
	g_data.g_heredoc_end = true;
	(void)sig;
  exit(1);
}

int ft_fork()
{
  g_data.g_forked = true;
  return fork();
}

int ret_wait(int pid)
{
  int status;

  status = 0;
  waitpid(pid, &status, 0);
  return status;
}
