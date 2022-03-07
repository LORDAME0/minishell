/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/07 19:38:52 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int n, char **args, char **env)
{
	t_token		*list;
	t_env		*denv;
	t_seq		*seq;
	char		*line;
	(void)n;
	(void)args;
	denv = dup_env(env); 

	seq = NULL;
	line = NULL;
	list = NULL;
	int Stdin = dup(0);
	int Stdout = dup(1);
	while (1)
	{
		line = readline("$> ");
		if (line == NULL || *line == '\0')
			continue ;
		tokenizer(&list, line);
		if (list && syntax_analysis(list) == false)
		{
			list = expander(list, denv);
			if (list)
				list = corrector(list);
			if (list)
			{
				seq = parser(list);
				if (seq == NULL)
					exit (1);
				eval_seq(seq, env);
			}
			list = NULL;
			seq = NULL;
			line = NULL;
		}
		dup2(Stdout, 1);
		dup2(Stdin, 0);
		/* dup2(1, Stdout); */
		/* dup2(0, Stdin); */
	}
		/* free_tokens(list2); */
		/* free_env(denv); */
		/* system("leaks minishell"); */
}
