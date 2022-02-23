/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:32:48 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/23 00:57:05 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	check_quotes_and_parens(t_list *tokens)
{
	bool		open_quotes;
	t_token		*current_token;
	int			matching_paren;

	current_token = NULL;
	open_quotes = false;
	matching_paren = 0;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		if (current_token->type == d_quote || current_token->type == s_quote)
			open_quotes = !open_quotes;
		if (current_token->type == o_parenthesis)
			matching_paren++;
		if (current_token->type == c_parenthesis)
			matching_paren--;
		tokens = tokens->next;
	}
	if (matching_paren || open_quotes)
		return (true);
	return (false);
}

bool	check_redirection(t_list *tokens)
{
	bool		unfulfilled;
	t_token		*current_token;

	current_token = NULL;
	unfulfilled = false;
	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		if (current_token->type == redirection && unfulfilled == false)
			unfulfilled = true;
		else if (current_token->type == word)
			unfulfilled = false;
		else if (current_token->type != space && unfulfilled == true)
			return (true);
		tokens = tokens->next;
	}
	if (unfulfilled)
		return (true);
	return (false);
}

bool	check_first_and_last(t_list *tokens)
{
	t_token	*last;
	t_token	*first;

	if (tokens == NULL)
		return (true);
	first = ((t_token *)tokens->content);
	last = ((t_token *)ft_lstlast(tokens)->content);
	if (first->type == and_if || first->type == or_if
		|| first->type == pip)
		return (true);
	if (last->type == and_if || last->type == or_if
		|| last->type == pip)
		return (true);
	return (false);
}

bool	check_pip_or_and(t_list *tokens)
{
	size_t	words;
	size_t	type;

	words = 0;
	if (tokens == NULL)
		return (true);
	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
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
		tokens = tokens->next;
	}
	return (false);
}

bool	syntax_analysis(t_list *tokens)
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
