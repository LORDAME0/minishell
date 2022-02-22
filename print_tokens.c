/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:12:03 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/22 20:15:29 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	print_tokens(t_list *tok_list)
{
	t_token	*token;

	while (tok_list)
	{
		token = tok_list->content;
		printf ("[%s] type : [%s]\n",
			token->elem, return_token_type(token->type));
		tok_list = tok_list->next;
	}
}

void	print_tokens_types(t_list *tok_list)
{
	t_token	*token;

	while (tok_list)
	{
		token = tok_list->content;
		printf ("[%s]", return_token_type(token->type));
		tok_list = tok_list->next;
	}
	printf ("\n");
}

void	re_print_command(t_list	*tok_list)
{
	t_token	*token;

	while (tok_list)
	{
		token = tok_list->content;
		printf ("%s", token->elem);
		tok_list = tok_list->next;
	}
	printf("\n");
}
