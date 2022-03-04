/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/04 13:30:30 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int n, char **args, char **env)
{
	t_token		*list;
	char		*line;
	(void)n;
	(void)args;
	(void)env;

	list = NULL;
	while (1)
	{
		line = readline("> ");
		add_history(line);
		tokenizer(&list, line);
		print_tokens(list);
		/* re_print_command(tok_list); */
		/* print_tokens_types(tok_list); */
		/* remove_redondant_space(&tok_list); */
		syntax_analysis(list);
		/* parser(&seq, list); */
		/* print_seq(seq); */
		/* ft_eval_seq(seq); */
		/* re_print_command(tok_list); */
		line = NULL;
		list = NULL;
	}
}
