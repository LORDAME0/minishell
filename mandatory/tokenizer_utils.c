/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/27 15:11:26 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*return_token_type(int type)
{
	if (type == 0)
		return ("redirection");
	else if (type == 1)
		return ("word");
	else if (type == 2)
		return ("pip");
	else if (type == 3)
		return ("space");
	else if (type == 4)
		return ("d_quote");
	else if (type == 5)
		return ("s_quote");
	else if (type == 6)
		return ("key");
	return (NULL);
}

bool	is_keyword(char c)
{
	if (c == '>'
		|| c == '<'
		|| c == '|'
		|| c == ' '
		|| (is_quote(c)))
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

char	*add_keyword_token(t_token **head, char *current)
{
	if ((*current == '>' || *current == '<'))
		redirection_token(head, current);
	else if (*current == '|')
		pip_token(head);
	else if (is_quote(*current))
		quote_token(head, current);
	else if (*current == ' ')
	{
		while (*(current + 1) == ' ')
			current++;
		if (*(current + 1) != '\0')
			space_token(head);
	}
	if (*current == *(current + 1)
		&& (*current == '>' || *current == '<'))
		current += 2;
	else
		current++;
	return (current);
}
