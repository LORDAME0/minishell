/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:12:03 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/25 18:18:51 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf ("[%s] type : [%s]\n",
			token->elem, return_token_type(token->type));
		token = token->next;
	}
}

void	print_tokens_types(t_token *token)
{
	while (token)
	{
		printf ("[%s]", return_token_type(token->type));
		token = token->next;
	}
	printf ("\n");
}

void	re_print_command(t_token	*token)
{
	while (token)
	{
		printf ("%s", token->elem);
		token = token->next;
	}
	printf("\n");
}
