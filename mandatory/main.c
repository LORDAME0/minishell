/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 06:39:32 by orahmoun         ###   ########.fr       */
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
	/* while (1) */
	/* { */
		line = readline("> ");
		add_history(line);
		tokenizer(&list, line);
		/* print_tokens(list); */
		syntax_analysis(list);
		/* printf ("***************\n"); */
		list = expander(list, denv);
		/* print_tokens(list2); */
		/* printf ("***************\n"); */
		/* print_tokens(corrector(list2)); */
		/* printf ("***************\n"); */
		/* line = NULL; */
		/* list = NULL; */
	/* } */
		free(line);
		free_tokens(list);
		/* free_tokens(list2); */
		free_env(denv);
		system("leaks minishell");
}
