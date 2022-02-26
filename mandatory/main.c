/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/25 19:05:01 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	t_token	*list;
	char	*line;

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
		/* re_print_command(tok_list); */
		line = NULL;
		list = NULL;
	}
}
