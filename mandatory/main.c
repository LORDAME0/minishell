/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/04 19:57:33 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int n, char **args, char **env)
{
	t_token		*list;
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
		print_tokens(expander(list, denv));
		line = NULL;
		list = NULL;
	}
}
