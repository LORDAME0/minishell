/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/14 01:04:54 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

void	signal_handling(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

int	main(int n, char **args, char **env)
{
	t_env		*denv;

	(void)n;
	(void)args;
	signal_handling();
	denv = dup_env(env);
	g_last_return = 0;
	shell_loop(&denv);
	free_env(denv);
}
