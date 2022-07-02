/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaamaou <rnaamaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/06/30 17:13:59 by rnaamaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handler(int sig)
{
	write(1, "\n", 1);
	if (sig == SIGINT && g_data.g_forked == false)
	{
		g_data.g_last_return = 1;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handling(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int n, char **args, char **env)
{
	char		*tmp;
	t_env		*denv;

	(void)n;
	(void)args;
	rl_catch_signals = 0;
	if (env == NULL || *env == NULL)
	{
		tmp = getcwd(NULL, 0);
		env = init_2d_array();
		env = add_element_2d_array_last(env,
				ft_strjoin_free(ft_strjoin("PWD", "="), tmp));
		env = add_element_2d_array_last(env,
				ft_strjoin_free(ft_strjoin("SHLVL", "="), "0"));
	}
	signal_handling();
	denv = dup_env(env);
	g_data.g_last_return = 0;
	shell_loop(&denv);
}
