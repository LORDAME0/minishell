/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/12 21:52:31 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int n, char **args, char **env)
{
	t_env		*denv;

	(void)n;
	(void)args;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	denv = dup_env(env); 
	g_global.last_return = 0;
	g_global.env = denv;
	shell_loop(&denv);
	free_env(denv);
	// system("leaks minishell");
}
