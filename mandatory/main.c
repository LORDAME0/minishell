/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 15:14:41 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int n, char **args, char **env)
{
	t_token		*list;
	/* t_token		*list2 = NULL; */
	t_env		*denv;
	char		*line;
	(void)n;
	(void)args;
	denv = dup_env(env); 

	list = NULL;
	while (1)
	{
		line = readline("> ");
		add_history(line);
		tokenizer(&list, line);
		print_tokens(list);
		syntax_analysis(list);
		printf ("***************\n");
		list = expander(list, denv);
		print_tokens(list);
		printf ("***************\n");
		list = corrector(list);
		print_tokens(list);
		printf ("***************\n");
		free(line);
		free_tokens(list);
		line = NULL;
		list = NULL;
	}
		/* free_tokens(list2); */
		/* free_env(denv); */
		/* system("leaks minishell"); */
}
