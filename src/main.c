/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hamd <ael-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/27 21:17:11 by ael-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_last_return = 1;
		write(1, "\n", 1);
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
	g_last_return = 0;
	shell_loop(&denv);
}
