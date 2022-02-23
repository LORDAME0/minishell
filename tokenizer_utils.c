/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:53:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/23 18:01:35 by orahmoun         ###   ########.fr       */
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

t_token	*create_token(char *elem, int type)
{
	t_token	*token;

	token = malloc (sizeof(token));
	token->elem = elem;
	token->type = type;
	return (token);
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

int	add_keyword_token(t_list **head, char *s, int i)
{
	if ((s[i] == '(' || s[i] == ')'))
		i = parenthesis_token(head, s, i);
	else if ((s[i] == '>' || s[i] == '<'))
		i = redirection_token(head, s, i);
	else if (((s[i] == '&' && s[i + 1] == '&') || s[i] == '|'))
		i = and_or_state_token(head, s, i);
	else if (is_quote(s[i]))
		i = quote_token(head, s, i);
	else if (s[i] == ' ')
	{
		while (s[i + 1] == ' ')
			i++;
		if (s[i + 1] != '\0')
			i = space_token(head, i);
		else
			i++;
	}
	return (i);
}
