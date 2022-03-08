/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/07 18:44:24 by orahmoun         ###   ########.fr       */
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
	t_seq *seq;

	seq = NULL;
	line = NULL;
	list = NULL;
	while (1)
	{
		line = readline("$> ");
		if (line == NULL || *line == '\0')
			continue ;
		add_history(line);
		tokenizer(&list, line);
		print_tokens(list);
				printf ("********************\n");
			list = expander(list, denv);
		print_tokens(list);
				printf ("********************\n");
				list = corrector(list);
		print_tokens(list);
		/* if (list && syntax_analysis(list) == false) */
		/* { */
		/* 	list = expander(list, denv); */
		/* 	if (list) */
		/* 	{ */
		/* 		list = corrector(list); */
		/* 		print_tokens(list); */
		/* 	} */
		/* 	if (list) */
		/* 	{ */
		/* 		printf ("********************\n"); */
		/* 		seq = parser(list); */
		/* 		if (seq == NULL) */
		/* 		{ */
		/* 			seq = NULL; */
		/* 			line = NULL; */
		/* 			list = NULL; */
		/* 			continue ; */
		/* 		} */
		/* 		eval_seq(seq, env); */
		/* 		seq = NULL; */
		/* 	} */
		free(line);
		free_tokens(list);
		list = NULL;
		line = NULL;
	}
		/* free_tokens(list2); */
		/* free_env(denv); */
		/* system("leaks minishell"); */
}
