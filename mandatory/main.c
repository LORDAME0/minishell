/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/10 22:23:07 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int n, char **args, char **env)
{
  t_env		*denv;

  (void)n;
	(void)args;
	denv = dup_env(env); 
	g_global.last_return = 0;
	signal(SIGINT, SIG_IGN);
	shell_loop(denv);
	free_env(denv);
	system("leaks minishell");
}
