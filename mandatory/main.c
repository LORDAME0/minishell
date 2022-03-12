/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/11 22:32:31 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// void handler(int sig)
// {
  // (void)sig;
  // signal(SIGINT, SIG_IGN);
  // ft_putstr_fd("\n", 1);
  // signal(SIGINT, handler);
// }

int	main(int n, char **args, char **env)
{
  t_env		*denv;

  (void)n;
	(void)args;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	denv = dup_env(env); 
	g_global.last_return = 0;
	shell_loop(&denv);
	free_env(denv);
	// system("leaks minishell");
}
