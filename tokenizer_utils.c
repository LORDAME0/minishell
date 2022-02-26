/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/26 17:30:21 by orahmoun         ###   ########.fr       */
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
		return ("and_if");
	else if (type == 4)
		return ("or_if");
	else if (type == 5)
		return ("space");
	else if (type == 6)
		return ("d_quote");
	else if (type == 7)
		return ("s_quote");
	else if (type == 8)
		return ("o_parenthesis");
	else if (type == 9)
		return ("c_parenthesis");
	return (NULL);
}

bool	is_keyword(char c, char n)
{
	if ((c == '(' || c == ')')
		|| (c == '>' || c == '<')
		|| (c == '&' && n == '&')
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
	if ((*current == '(' || *current == ')'))
		parenthesis_token(head, current);
	else if ((*current == '>' || *current == '<'))
		redirection_token(head, current);
	else if (((*current == '&' && *(current + 1) == '&') || *current == '|'))
		and_or_pip_token(head, current);
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
		&& ((*current == '|' || *current == '&')
			|| (*current == '>' || *current == '<')))
		current += 2;
	else
		current++;
	return (current);
}
