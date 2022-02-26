/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:13:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/26 17:32:09 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "tokenizer.h"
#define LINE_END 0
#define RESET_STATIC 0

bool	is_inside_quotes(char c)
{
	static char		open = -1;

	if (c == RESET_STATIC)
	{
		open = -1;
		return (false);
	}
	if (is_quote(c))
	{
		if (open == -1)
		{
			open = c;
			return (false);
		}
		else if (c == open)
		{
			open = -1;
			return (false);
		}
	}
	else if (open == -1)
		return (false);
	return (true);
}

char	*chop_word(t_token **tokens, char *current)
{
	char	*start;
	t_token	*last_token;
	char	quote;

	quote = -1;
	start = current;
	if (*tokens)
	{
		last_token = get_last_token(*tokens);
		if (last_token->type == s_quote)
			quote = '\'';
		if (last_token->type == d_quote)
			quote = '\"';
	}
	while (*current)
	{
		if (is_keyword(*current) == true && quote == -1)
			break ;
		if (quote == *current)
			break ;
		current++;
	}
	add_word_token(tokens, start, current);
	return (current);
}

void	tokenizer(t_token **tokens, char *s)
{
	char		*start;
	char		*current;

	start = s;
	current = start;
	while (*current)
	{
		if (is_keyword(*current)
			&& is_inside_quotes(*current) == false)
			current = add_keyword_token(tokens, current);
		else
			current = chop_word(tokens, current);
		start = current;
	}
	is_inside_quotes(RESET_STATIC);
}
