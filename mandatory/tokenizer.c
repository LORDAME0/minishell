/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:13:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/10 22:40:16 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
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

char	*chop_key(t_token **tokens, char *current)
{
	char	*start;

	start = current;
	if (*current == '?')
		current++;
	else
	{
		while (ft_isalnum(*current) || *current == '_')
			current++;
	}
	if (start != current)
		add_key_token(tokens, start, current);
	else
		add_word_token(tokens, start - 1, current);
	return (current);
}

char	*chop_word(t_token **tokens, char *current, bool open, bool heredoc)
{
	char	*start;
	char	quote;

	panic(tokens == NULL, "NULL PARAM", __func__);
	quote = -1;
	start = current;
	if (open && *tokens && get_last_token(*tokens)->type == s_quote)
		quote = '\'';
	else if (open && *tokens && get_last_token(*tokens)->type == d_quote)
		quote = '\"';
	while (*current)
	{
		if (*current == '$' && (quote != '\'' || !open) && !heredoc)
		{
			add_word_token(tokens, start, current);
			current = chop_key(tokens, ++current);
			start = current;
		}
		else if ((is_keyword(*current) == true && open == false)
			|| quote == *current)
			break ;
		else
			current++;
	}
	add_word_token(tokens, start, current);
	return (current);
}

void	tokenizer(t_token **tokens, char *s)
{
	char		*start;
	char		*current;
	bool		open_quote;
	bool		heredoc;
	
	panic(s == NULL, "PARAM IS NULL", __func__);
	start = s;
	current = start;
	open_quote = false;
	while (*current)
	{
		if (is_quote(*current))
			open_quote = !open_quote;
		if (*current == '<' && *(current + 1) == '<')
			heredoc = true;
		else if (heredoc == true && get_last_token(*tokens)->type == word)
			heredoc = false;
		if (is_keyword(*current)
			&& is_inside_quotes(*current) == false)
			current = add_keyword_token(tokens, current, !open_quote);
		else
			current = chop_word(tokens, current, open_quote, heredoc);
		start = current;
	}
	is_inside_quotes(RESET_STATIC);
}
