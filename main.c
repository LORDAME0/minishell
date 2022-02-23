/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/23 01:17:43 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	t_list	*tok_list;
	char	*line;

	tok_list = NULL;
	while (1)
	{
		line = readline("> ");
		add_history(line);
		tokenizer(&tok_list, line);
		print_tokens(tok_list);
		/* re_print_command(tok_list); */
		/* print_tokens_types(tok_list); */
		/* remove_redondant_space(&tok_list); */
		syntax_analysis(tok_list);
		/* re_print_command(tok_list); */
		expander(tok_list);
		line = NULL;
		tok_list = NULL;
	}
}
