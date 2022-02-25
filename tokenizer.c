/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:13:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/25 18:29:30 by orahmoun         ###   ########.fr       */
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

void	tokenizer(t_token **head, char *s)
{
	int		start;
	int		current;

	start = 0;
	current = 0;
	while (1337)
	{
		if (is_keyword(s[current], s[current + 1])
			&& is_inside_quotes(s[current]) == false)
		{
			add_word_token(head, s + start, current - start);
			current = add_keyword_token(head, s, current);
			start = current;
		}
		else if (s[current] == LINE_END)
		{
			add_word_token(head, s + start, current - start);
			break ;
		}
		else
			current++;
	}
	is_inside_quotes(RESET_STATIC);
}
