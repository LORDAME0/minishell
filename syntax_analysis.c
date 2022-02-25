/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:32:48 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/25 19:01:02 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	check_quotes_and_parens(t_token *token)
{
	bool		open_quotes;
	int			matching_paren;

	open_quotes = false;
	matching_paren = 0;
	while (token)
	{
		if (token->type == d_quote || token->type == s_quote)
			open_quotes = !open_quotes;
		if (token->type == o_parenthesis)
			matching_paren++;
		if (token->type == c_parenthesis)
			matching_paren--;
		token = token->next;
	}
	if (matching_paren || open_quotes)
		return (true);
	return (false);
}

bool	check_redirection(t_token *token)
{
	bool		unfulfilled;

	unfulfilled = false;
	while (token)
	{
		if (token->type == redirection && unfulfilled == false)
			unfulfilled = true;
		else if (token->type == word)
			unfulfilled = false;
		else if (token->type != space && unfulfilled == true)
			return (true);
		token = token->next;
	}
	if (unfulfilled)
		return (true);
	return (false);
}

bool	check_first_and_last(t_token *token)
{
	t_token	*last;
	t_token	*first;

	if (token == NULL)
		return (true);
	first = token;
	last = get_last_token(token);
	if (first->type == and_if || first->type == or_if
		|| first->type == pip)
		return (true);
	if (last->type == and_if || last->type == or_if
		|| last->type == pip)
		return (true);
	return (false);
}

bool	check_pip_or_and(t_token *token)
{
	size_t	words;
	size_t	type;

	words = 0;
	if (token == NULL)
		return (true);
	while (token)
	{
		type = token->type;
		if (type == word)
			words++;
		else if (type == and_if || type == or_if
			|| type == pip)
		{
			if (words == 0)
				return (true);
			else if (words != 0)
				words = 0;
		}
		token = token->next;
	}
	return (false);
}

bool	syntax_analysis(t_token *tokens)
{
	if (check_quotes_and_parens(tokens)
		|| check_redirection(tokens)
		|| check_first_and_last(tokens)
		|| check_pip_or_and(tokens))
	{
		printf ("MiniSHELL :: syntax error\n");
	}
	return (false);
}
