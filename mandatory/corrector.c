/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 01:42:37 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/05 06:18:23 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// to_do
// remove quotes bc they are useless after the expander
// also join the word without separator
// removing the white space
//
#include "main.h"

/* ft_strappened(char dst, char src) */
/* { */

/* } */

t_token	*joiner(t_token *token)
{
	t_token *new;
	t_token *tmp;
	char	*str;
	
	new = NULL;
	str = ft_strdup("");
	ft_assert(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		if (token->type == word)
		{
			while (token && token->type == word)
			{
				str = ft_strjoin(str, token->elem);	
				free(token->elem);
				tmp = token->next;
				free(token);
				token = tmp;
			}
			add_token_back(&new, create_token(str, word));
			str = ft_strdup("");
		}
		if (token != NULL && token->type != space)
		{
			token->next = NULL;
			add_token_back(&new, token);
		}
		if (token == NULL)
			break ;
		token = tmp;
	}
	return (new);
}

t_token	*remove_quotes(t_token *token)
{
	t_token *new;
	t_token *tmp;
	
	new = NULL;
	ft_assert(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type != s_quote
			&& token->type != d_quote)
			add_token_back(&new, token);
		token = tmp;
	}
	return (new);
}

t_token	*corrector(t_token *token)
{
	ft_assert(token == NULL, "NULL PARAM", __func__);
	token = remove_quotes(token);
	token = joiner(token);

	return (token);
}
