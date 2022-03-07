/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 01:42:37 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/07 19:10:06 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

t_token	*joiner(t_token *token)
{
	t_token	*new;
	t_token	*tmp;
	char	*str;

	new = NULL;
	ft_assert(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		if (token->type == word)
		{
			str = ft_strdup("");
			while (token && token->type == word)
			{
				tmp = token->next;
				str = ft_strjoin_free(str, token->elem);
				free(token->elem);
				free(token);
				token = tmp;
			}
			add_token_back(&new, create_token(str, word));
			free (str);
		}
		if (token && token->type != space)
		{
			tmp = token->next;
			token->next = NULL;
			add_token_back(&new, token);
		}
		token = tmp;
	}
	return (new);
}

t_token	*remove_space(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	ft_assert(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type != space)
			add_token_back(&new, token);
		else
		{
			free(token->elem);
			free(token);
			token = NULL;
		}
		token = tmp;
	}
	return (new);
}

t_token	*remove_quotes(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	ft_assert(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type != s_quote
			&& token->type != d_quote)
			add_token_back(&new, token);
		else
		{
			free(token->elem);
			free(token);
			token = NULL;
		}
		token = tmp;
	}
	return (new);
}

t_token	*corrector(t_token *token)
{
	ft_assert(token == NULL, "NULL PARAM", __func__);
	token = remove_quotes(token);
	token = joiner(token);
	/* token = remove_space(token); */
	return (token);
}
